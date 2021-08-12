#include<SFML/Graphics.hpp>
#include"appearanceconfig.hpp"

class Background
 : public sf::RectangleShape
{
public:
    Background(std::string& imageUrl, BackgroundPosition pos);
    sf::Texture texture;
private:
    void drawTileTexture();
};