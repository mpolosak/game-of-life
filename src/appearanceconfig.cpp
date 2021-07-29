#include "appearanceconfig.hpp"
#include "utilities.hpp"
#include<iomanip>

void AppearanceConfig::setColors(std::string& colorsString)
{
    std::smatch base_match;
    try{
        base_match = match(colorsString, "([0-f]{6})/([0-f]{6})/([0-f]{6})");
    }
    catch(...)
    {
        throw std::string(
            "Colors must be written in hex as live_cell_colour/death_cell_colour/background i.e. 609060/ffffff/909090"
        );
    }
    
    std::string live_cell_color_string = base_match[1];
    std::string dead_cell_color_string = base_match[2];
    std::string background_color_string = base_match[3];

    liveCellColor = colorFromHex(live_cell_color_string);
    deadCellColor = colorFromHex(dead_cell_color_string);
    backgroundColor = colorFromHex(background_color_string);

    this->colorsString = colorsString;
}

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config)
{
    return os
        << std::setw(20) << "Live cell color" << " : "
            << config.liveCellColor << std::endl
        << std::setw(20) << "Dead cell color" << " : "
            << config.deadCellColor << std::endl
        << std::setw(20) << "Background color" << " : "
            << config.backgroundColor << std::endl;
}