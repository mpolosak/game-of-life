#include<iostream>
#include<string>
#include<SFML/System/Clock.hpp>
#include"board.hpp"
#include"config.hpp"

sf::RenderWindow window;
sf::VideoMode windowVideoMode;
int style = sf::Style::Default;
sf::View view;
Board *board;
bool inDrawingMode = false;

void init(int argc, char *argv[]);
void run();
void processEvents();
void setViewSize(int width, int height);
void draw();
void handleEvent(sf::Event &event);
void handleKeyPress(sf::Keyboard::Key key);
void setHoveredBlockValue(bool value);
void drawBoard();
void setFullscreen(bool fullscreen);
void toggleFullscreen();

int main(int argc, char *argv[])
{
    init(argc, argv);    
    run();
    return 0;
}

void init(int argc, char *argv[])
{
    Config config;
    try
    {
        config = Config::fromCommandLine(argc,argv);
    }
    catch(std::string &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    catch(int error)
    {
        std::exit(0);
    }

    std::cout<<config;

    board = new Board(config.board);
    
    windowVideoMode=sf::VideoMode(config.width, config.height);
    setFullscreen(config.fullscreen);

    if(config.board.method==BoardMethod::Draw)
        drawBoard();
    else
        board->fillWithRandomValues();
}

void run()
{
    sf::Clock clock;
    draw();
    while (window.isOpen())
    {
        processEvents();

        auto miliseconds = clock.getElapsedTime().asMilliseconds();
        if(miliseconds>=250)
        {
            clock.restart();
            
            board->step();
                
            draw();
        }
    }
}

void processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
        handleEvent(event);

}

void setViewSize(int width, int height)
{
    sf::FloatRect rect=sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(width,height));
    view.reset(rect);
    window.setView(view);
    board->setBlockSize(std::min(width/board->getWidth(),height/board->getHeight()));
}

void draw()
{
    window.clear(sf::Color(150, 150, 150));
    window.draw(*board);
    window.display();
}

void handleEvent(sf::Event &event)
{
    switch(event.type)
    {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            handleKeyPress(event.key.code);
            break;
        case sf::Event::Resized:
            setViewSize(event.size.width,event.size.height);
            break;
        default:
            break;
    } 
    draw();
}

void handleKeyPress(sf::Keyboard::Key key)
{
    switch(key)
    {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case  sf::Keyboard::F11:
            toggleFullscreen(); 
            break;
        case sf::Keyboard::Return:
            inDrawingMode = false;
            break;
        default:
            break;
    }
}

void setHoveredBlockValue(bool value)
{
    sf::Vector2i position = sf::Mouse::getPosition(window);
    int blockSize = board->getBlockSize();
    int x = position.x/blockSize;
    int y = position.y/blockSize;
    board->setBlockValue(x, y, value);
    draw();
}

void drawBoard()
{
    inDrawingMode = true;
    board->clear();
    draw();
    while(window.isOpen()&&inDrawingMode)
    {
        processEvents();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            setHoveredBlockValue(true);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            setHoveredBlockValue(false);
    }
}

void setFullscreen(bool fullscreen)
{
    sf::VideoMode newVideoMode;
    if(fullscreen)
    {
        style = sf::Style::Fullscreen;
        newVideoMode = sf::VideoMode::getDesktopMode();
    }
    else
    {
        style=sf::Style::Default;
        newVideoMode = windowVideoMode;
    }
    window.create(newVideoMode,"Game of life",style);
    setViewSize(newVideoMode.width,newVideoMode.height);
}

void toggleFullscreen()
{
    if(style==sf::Style::Default)
        setFullscreen(true);
    else
        setFullscreen(false);
}