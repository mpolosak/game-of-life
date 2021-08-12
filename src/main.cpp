#include"main.hpp"

sf::RenderWindow window;
Config config;
int style = sf::Style::Default;
sf::View view;
std::unique_ptr<Board> board;
std::unique_ptr<sf::RectangleShape> background;
std::unique_ptr<sf::Texture> backgroundTexture;

int main(int argc, char *argv[])
{
    init(argc, argv);    
    run();
    return 0;
}

void init(int argc, char *argv[])
{
    try
    {
        config = Config::fromCommandLine(argc,argv);
        board = std::make_unique<Board>(&config.board, config.appearance);
        if(config.appearance.backgroundUrl!="")
            loadBackground();
    }
    catch(std::string &error)
    {
        std::cerr<<error<<std::endl;
        std::exit(1);
    }
    
    std::cout<<config;

    setFullscreen(config.fullscreen);
}

void run()
{
    sf::Clock clock;
    draw();
    while (window.isOpen())
    {
        processEvents();

        if(config.board.draw)
            processDrawMode();
        else
        {
            auto miliseconds = clock.getElapsedTime().asMilliseconds();
            if(miliseconds>=250)
            {
                clock.restart();
            
                board->step();
                
                draw();
            }
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
    board->setBlockSize(std::min(width/config.board.width,height/config.board.height));
    setBackgroundSize(width, height);
}

void draw()
{
    window.clear(config.appearance.backgroundColor);
    if(background)
        window.draw(*background);
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
            config.board.draw = false;
            break;
        case sf::Keyboard::Tab:
            config.board.draw = !config.board.draw;
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

void processDrawMode()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        setHoveredBlockValue(true);
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        setHoveredBlockValue(false);
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
        newVideoMode = sf::VideoMode(config.width, config.height);
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

void loadBackground()
{
    backgroundTexture = std::make_unique<sf::Texture>();
    if (!backgroundTexture->loadFromFile(config.appearance.backgroundUrl))
        throw std::string("Cannot load texture from file '"
            + config.appearance.backgroundUrl + "'\n");
    background = std::make_unique<sf::RectangleShape>();
    background->setTexture(backgroundTexture.get()); 
    if(config.appearance.backgroundPosition==BackgroundPosition::tile)
        backgroundTexture->setRepeated(true);
}

void setBackgroundSize(int width, int height)
{
    background->setSize(sf::Vector2f(width,height));
}