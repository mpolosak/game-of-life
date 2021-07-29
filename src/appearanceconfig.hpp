#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
class AppearanceConfig
{
public:
    void setColours(std::string& coloursString);
    std::string getColours(){return coloursString;};
    sf::Color liveCellColour;
    sf::Color deadCellColour;
    sf::Color backgroundColour;
private:
    std::string coloursString;
};

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config);