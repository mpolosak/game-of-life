#include"background.hpp"
#include<cmath>

Background::Background(std::string& imageUrl, BackgroundPosition position)
: position(position)
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
    }
    setTexture(&texture); 
}

void Background::setSize(const sf::Vector2f& size)
{
    sf::RectangleShape::setSize(size);
    if(position == BackgroundPosition::tile)
    {
        sf::IntRect rect = sf::IntRect(0, 0, size.x, size.y);
        setTextureRect(rect);
    }
}

void Background::drawTileTexture()
{
    auto screenRes = sf::VideoMode::getDesktopMode();
    auto textureRes = texture.getSize();
    int horizontalRatio = std::ceil((float)screenRes.width/textureRes.x);
    int verticalRatio = std::ceil((float)screenRes.height/textureRes.y);

    sf::RenderTexture renderTexture;
    renderTexture.create(screenRes.width, screenRes.height);
    sf::Sprite sprite = sf::Sprite(image);

    for(int x = 0; x<horizontalRatio; x++)
    {
        for(int y = 0; y<verticalRatio; y++)
        {
            sprite.setPosition(x*textureRes.x, y*textureRes.y);
            renderTexture.draw(sprite);
        }
    }

    renderTexture.display();
    texture = renderTexture.getTexture();
}