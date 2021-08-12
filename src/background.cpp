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
            texture = image;
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
            drawCenterTexture(size);
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

void Background::drawCenterTexture(const sf::Vector2f& size)
{
    auto imageRes = image.getSize();
    float x = (size.x - imageRes.x) / 2;
    float y = (size.y - imageRes.y) / 2;

    sf::RenderTexture renderTexture;
    renderTexture.create(size.x, size.y);
    renderTexture.clear(fillColor);
    sf::Sprite sprite = sf::Sprite(image);
    sprite.setPosition(x, y);
    renderTexture.draw(sprite);

    renderTexture.display();
    texture = renderTexture.getTexture();
}