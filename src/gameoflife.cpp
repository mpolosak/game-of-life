#include"gameoflife.h"

GameOfLife::GameOfLife(int argc, char *argv[])
{
    config = Config::fromCommandLine(argc,argv);
    board = std::make_unique<Board>(&config.board, config.appearance);
    if(config.appearance.backgroundUrl!="")
        background = std::make_unique<Background>(
            config.appearance.backgroundUrl,
            config.appearance.backgroundPosition,
            config.appearance.backgroundColor
        );
    std::cout<<config;
    setFullscreen(config.fullscreen);
}

void GameOfLife::run()
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

void GameOfLife::setFullscreen(bool fullscreen)
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

void GameOfLife::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
        handleEvent(event);
}

void GameOfLife::handleEvent(sf::Event &event)
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

void GameOfLife::draw()
{
    window.clear(config.appearance.backgroundColor);
    if(background)
        window.draw(*background);
    window.draw(*board);
    window.display();
}

void GameOfLife::setViewSize(int width, int height)
{
    sf::FloatRect rect=sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(width,height));
    view.reset(rect);
    window.setView(view);
    board->handleNewViewSize(width, height);
    if(background)
        background->setSize(sf::Vector2f(width,height));
}

void GameOfLife::handleKeyPress(sf::Keyboard::Key key)
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

void GameOfLife::toggleFullscreen()
{
    if(style==sf::Style::Default)
        setFullscreen(true);
    else
        setFullscreen(false);
}

void GameOfLife::processDrawMode()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        setHoveredBlockValue(true);
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        setHoveredBlockValue(false);
}

void GameOfLife::setHoveredBlockValue(bool value)
{
    auto [x, y] = sf::Mouse::getPosition(window);
    if(x<0||y<0) return;
    board->setBlockOnPos({(uint)x, (uint)y}, value);
    draw();
}