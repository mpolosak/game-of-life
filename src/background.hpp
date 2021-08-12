#include<SFML/Graphics.hpp>
#include"appearanceconfig.hpp"

class Background
 : public sf::RectangleShape
{
public:
    Background(std::string& imageUrl, BackgroundPosition position);
    void setSize(const sf::Vector2f& size);
    BackgroundPosition position;
    sf::Texture texture;
    sf::Texture image; 
private:
    void drawTileTexture();
};