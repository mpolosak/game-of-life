#include"background.hpp"
#include<cmath>

Background::Background(std::string& imageUrl, BackgroundPosition position,
    sf::Color fillColor)
: position(position), fillColor(fillColor)
{
    if (!image.loadFromFile(imageUrl))
        throw std::string("Cannot load texture from file '"
            + imageUrl + "'\n");

    switch(position)
    {
        case BackgroundPosition::tile:
            drawTileTexture();
            break;
        case BackgroundPosition::streatch:
        case BackgroundPosition::fill:
            texture = image;
            break;
        case BackgroundPosition::center:
            drawCenterTexture();
            break;
    }
    setTexture(&texture); 
}

void Background::setSize(const sf::Vector2f& size)
{
    sf::RectangleShape::setSize(size);
    switch(position)
    {
        case BackgroundPosition::tile:
        {
            sf::IntRect rect = sf::IntRect(0, 0, size.x, size.y);
            setTextureRect(rect);
            break;
        }
        case BackgroundPosition::center:
        {
            auto screenRes = sf::VideoMode::getDesktopMode();
            int x = (screenRes.width-size.x)/2;
            int y = (screenRes.height-size.y)/2;

            sf::IntRect rect = sf::IntRect(x, y, size.x, size.y);
            setTextureRect(rect);
            break;
        }
        case BackgroundPosition::fill:
        {
            auto texRes = texture.getSize();
            int x1 = texRes.x;
            int y1 = size.y/size.x*x1;
            if(y1>texRes.y)
            {
                y1 = texRes.y;
                x1 = size.x/size.y*y1;
            }
            int x0 = (texRes.x-x1)/2;
            int y0 = (texRes.y-y1)/2;
            sf::IntRect rect = sf::IntRect(x0, y0, x1, y1);
            setTextureRect(rect);
            break;
        }
        case BackgroundPosition::fit:
            drawFitTexture(size);
            break;
    }
}

void Background::drawTileTexture()
{
    auto screenRes = sf::VideoMode::getDesktopMode();
    auto imageRes = image.getSize();
    int horizontalRatio = std::ceil((float)screenRes.width/imageRes.x);
    int verticalRatio = std::ceil((float)screenRes.height/imageRes.y);

    sf::RenderTexture renderTexture;
    renderTexture.create(screenRes.width, screenRes.height);
    sf::Sprite sprite = sf::Sprite(image);

    for(int x = 0; x<horizontalRatio; x++)
    {
        for(int y = 0; y<verticalRatio; y++)
        {
            sprite.setPosition(x*imageRes.x, y*imageRes.y);
            renderTexture.draw(sprite);
        }
    }

    renderTexture.display();
    texture = renderTexture.getTexture();
}

void Background::drawCenterTexture()
{
    auto screenRes = sf::VideoMode::getDesktopMode();
    auto imageRes = image.getSize();

    sf::RenderTexture renderTexture;
    renderTexture.create(screenRes.width, screenRes.height);
    
    int x = (screenRes.width-imageRes.x)/2;
    int y = (screenRes.height-imageRes.y)/2;

    sf::Sprite sprite = sf::Sprite(image);
    sprite.setPosition(x, y);
    renderTexture.draw(sprite);

    renderTexture.display();
    texture = renderTexture.getTexture();
}

void Background::drawFitTexture(const sf::Vector2f& size)
{
    auto imageRes = image.getSize();

    int x0 = size.x;
    int y0 = (float)imageRes.y/imageRes.x*x0;
    if(y0>size.y)
    {
        y0 = size.y;
        x0 = (float)imageRes.x/imageRes.y*y0;
    }

    int x1 = (size.x-x0)/2;
    int y1 = (size.y-y0)/2;

    sf::RenderTexture renderTexture;
    renderTexture.create(size.x, size.y);

    renderTexture.clear(fillColor);

    sf::RectangleShape shape;
    shape.setTexture(&image);
    shape.setSize(sf::Vector2f(x0, y0));
    shape.setPosition(x1, y1);
    renderTexture.draw(shape);

    renderTexture.display();
    texture = renderTexture.getTexture();

    setTexture(&texture, true);
}