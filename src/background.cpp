#include"background.hpp"

Background::Background(std::string& imageUrl, BackgroundPosition pos)
{
    if (!texture.loadFromFile(imageUrl))
        throw std::string("Cannot load texture from file '"
            + imageUrl + "'\n");
    setTexture(&texture); 
}