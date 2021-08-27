#include "appearanceconfig.hpp"
#include "utilities.hpp"
#include<iomanip>
#include<boost/program_options.hpp>

namespace po = boost::program_options;

void AppearanceConfig::setColors(std::string& colorsString)
{
    std::smatch base_match;
    try{
        base_match = match(colorsString, "([0-f]{6})/([0-f]{6})/([0-f]{6})");
    }
    catch(...)
    {
        throw std::string(
            "Colors must be written in hex as live_cell_color/death_cell_color/background i.e. 609060/ffffff/909090"
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
            << config.backgroundColor << std::endl
        << std::setw(20) << "Background" << " : "
            << (config.backgroundUrl!="" ? '"' + config.backgroundUrl + '"' : "no")
            << std::endl
        << std::setw(20) << "Background position" << " : "
            << config.backgroundPosition << std::endl;
}

std::istream& operator>>(std::istream& is, BackgroundPosition& pos)
{
    std::string value;
    is >> value;

    if(value=="fill") pos=BackgroundPosition::fill;
    else if(value=="fit") pos=BackgroundPosition::fit;
    else if(value=="tile") pos=BackgroundPosition::tile;
    else if(value=="streatch") pos=BackgroundPosition::streatch;
    else if(value=="center") pos=BackgroundPosition::center;
    else throw po::invalid_option_value(value);

    return is;
}

std::ostream& operator<<(std::ostream& os, const BackgroundPosition& pos)
{
    switch(pos)
    {
        case BackgroundPosition::fill:
            return os << "fill";
        case BackgroundPosition::fit:
            return os << "fit";
        case BackgroundPosition::tile:
            return os << "tile";
        case BackgroundPosition::streatch:
            return os << "streatch";
        case BackgroundPosition::center:
            return os << "center";
    }
}