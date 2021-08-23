#include<SFML/Graphics.hpp>
#include"appearanceconfig.hpp"

class Background
 : public sf::RectangleShape
{
public:
    Background(std::string& imageUrl, BackgroundPosition position, sf::Color fillColor);
    void setSize(const sf::Vector2f& size);
private:
    void drawTileTexture();
    void drawCenterTexture();
    BackgroundPosition position;
    sf::Texture texture;
    sf::Texture image;
    sf::Color fillColor; 
};