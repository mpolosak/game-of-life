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

enum class BoardPosition{
    topleft,
    top,
    topright,
    right,
    bottomright,
    bottom,
    bottomleft,
    left,
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
    BoardPosition boardPosition;
private:
    std::string colorsString;
};

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config);
std::istream& operator>>(std::istream& is, BackgroundPosition& pos); 
std::ostream& operator<<(std::ostream& os, const BackgroundPosition& pos);
std::istream& operator>>(std::istream& is, BoardPosition& pos); 
std::ostream& operator<<(std::ostream& os, const BoardPosition& pos);
