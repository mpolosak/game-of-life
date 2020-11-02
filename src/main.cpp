#include<iostream>
#include<string>
#include<SFML/System/Clock.hpp>
#include"board.hpp"
#include"parsing.hpp"

sf::RenderWindow window;
sf::VideoMode windowVideoMode;
int style = sf::Style::Default;
sf::View view;
Board *board;

void init(int argc, char *argv[]);
void setViewSize(int width, int height);
void draw();
void handleEvent(sf::Event &event);
void setHoveredBlockValue(bool value);
void drawBoard();
void setFullscreen(bool fullscreen);

int main(int argc, char *argv[])
{
    try{
        init(argc, argv);
    }
    catch(char const* error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    catch(int error)
    {
        return 0;
    }
    
    sf::Clock clock;
    draw();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            handleEvent(event);

        if(clock.getElapsedTime().asMilliseconds()>=250)
        {
            clock.restart();
            
            board->step();
                
            draw();
        }
    }
    return 0;
}
void init(int argc, char *argv[])
{
    Config config;
    try
    {
        config = parseComandLine(argc,argv);
    }
    catch(...)
    {
        throw;
    }

    board = new Board(config.width, config.height, config.minBlockSize);

    board->survive=config.survive;
    board->birth=config.birth;
    
    windowVideoMode=sf::VideoMode(config.windowWidth, config.windowHeight);
    setFullscreen(config.fullscreen);

    if(config.draw)
        drawBoard();
    else
        board->fillWithRandomValues();
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
    if (
        event.type == sf::Event::KeyPressed 
        && event.key.code == sf::Keyboard::Escape
        || event.type == sf::Event::Closed
    )
        window.close();
    else if(
        event.type==sf::Event::KeyPressed
        && event.key.code == sf::Keyboard::F11
    )
    {
        if(style==sf::Style::Default)
            setFullscreen(true);
        else
            setFullscreen(false);
        draw();
    }
    else if(event.type == sf::Event::Resized)
    {
        setViewSize(event.size.width,event.size.height);
        draw();
    }
}

void setHoveredBlockValue(bool value)
{
    sf::Vector2i position = sf::Mouse::getPosition(window);
    board->setBlockValue(position.x/board->getBlockSize(),position.y/board->getBlockSize(),value);
    draw();
}

void drawBoard()
{
    board->clear();
    draw();
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (
                event.type == sf::Event::KeyPressed 
                && event.key.code == sf::Keyboard::Enter
            )
                return;
            else
                handleEvent(event);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            setHoveredBlockValue(true);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            setHoveredBlockValue(false);
    }
}

void setFullscreen(bool fullscreen)
{
    if(fullscreen)
    {
        style=sf::Style::Fullscreen;
        auto fullscreenMode = sf::VideoMode::getDesktopMode();
        window.create(fullscreenMode,"Game of life",style);
        setViewSize(fullscreenMode.width,fullscreenMode.height);
    }
    else
    {
        style=sf::Style::Default;
        window.create(windowVideoMode,"Game of life",style);
        setViewSize(windowVideoMode.width,windowVideoMode.height);
    }
}