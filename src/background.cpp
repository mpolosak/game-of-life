#include"background.hpp"
#include<cmath>

Background::Background(std::string& imageUrl, BackgroundPosition pos)
{
    if (!texture.loadFromFile(imageUrl))
        throw std::string("Cannot load texture from file '"
            + imageUrl + "'\n");

    if(pos == BackgroundPosition::tile)
        drawTileTexture();
    
    setTexture(&texture); 
}

void Background::drawTileTexture()
{
    auto screenRes = sf::VideoMode::getDesktopMode();
    auto textureRes = texture.getSize();
    int horizontalRatio = std::ceil((float)screenRes.width/textureRes.x);
    int verticalRatio = std::ceil((float)screenRes.height/textureRes.y);

    sf::RenderTexture renderTexture;
    renderTexture.create(screenRes.width, screenRes.height);
    sf::Sprite sprite = sf::Sprite(texture);

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