#pragma once
#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

class AppearanceConfig
{
public:
    void setColors(std::string& colorsString);
    std::string getColors(){return colorsString;};
    sf::Color liveCellColor;
    sf::Color deadCellColor;
    sf::Color backgroundColor;
    std::string backgroundUrl;
private:
    std::string colorsString;
};

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config);