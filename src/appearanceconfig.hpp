#pragma once
#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

enum BackgroundPosition{
    fill,
    fit,
    tile,
    streatch,
    center
};

class AppearanceConfig
{
public:
    void setColors(std::string& colorsString);
    std::string getColors(){return colorsString;};
    sf::Color liveCellColor;
    sf::Color deadCellColor;
    sf::Color backgroundColor;
    std::string backgroundUrl;
    BackgroundPosition backgroundPosition;
private:
    std::string colorsString;
};

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config);
std::istream& operator>>(std::istream& is, BackgroundPosition& pos); 
std::ostream& operator<<(std::ostream& os, const BackgroundPosition& pos);