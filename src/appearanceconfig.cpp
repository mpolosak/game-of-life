#include "appearanceconfig.hpp"
#include "utilities.hpp"
void AppearanceConfig::setColours(std::string& coloursString)
{
    std::smatch base_match;
    try{
        base_match = match(coloursString, "#([0-f]{6})/#([0-f]{6})/#([0-f]{6})");
    }
    catch(...)
    {
        throw std::string(
            "Colours must be written in hex as\
            live_cell_colour/death_cell_colour/background\
            i.e. #609060/#ffffff/#909090"
        );
    }
    
    std::string live_cell_colour_string = base_match[1];
    std::string dead_cell_colour_string = base_match[2];
    std::string background_colour_string = base_match[3];

    liveCellColour = colorFromHex(live_cell_colour_string);
    deadCellColour = colorFromHex(dead_cell_colour_string);
    backgroundColour = colorFromHex(background_colour_string);

    this->coloursString = coloursString;
}

std::ostream& operator<<(std::ostream& os, const AppearanceConfig& config)
{
    // To be implemented
}