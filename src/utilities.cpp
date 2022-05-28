#include"utilities.hpp"
#include<iomanip>
#include<set>
#include<algorithm>

std::smatch match(
    const std::string &string, const std::string &regex)
{
    std::smatch base_match;
    const std::regex base_regex(regex);
    if(std::regex_match(string, base_match, base_regex))
        return base_match;
    else
        throw 1;
}

std::pair<unsigned int,unsigned int> parseSize(const std::string &size)
{
    std::smatch base_match;

    try
    {
        base_match = match(size, "([0-9]*)x([0-9]*)");
    }
    catch(...)
    {
        throw std::string("The size must be written as widthxheight, i.e. 192x108");
    }

    std::string width_string=base_match[1];
    std::string height_string=base_match[2];

    unsigned int width = std::stoi(width_string);
    unsigned int height = std::stoi(height_string);

    if(width==0||height==0)
        throw std::string("Neither height nor width cannot be equal to zero");
    
    return std::make_pair(width,height); 
}

bool isImage(const std::string &path)
{
    const std::set<std::string> supportedImageFormats = {
        ".bmp", ".png", ".tga", //".jpg"
    };
    auto size = path.size();
    if(size<4) return false;
    std::string extension = path.substr(size-4,4);
    std::for_each(extension.begin(), extension.end(), [](char &ch){ch = std::tolower(ch);});
    return supportedImageFormats.count(extension);
}

sf::Color colorFromHex(std::string& hex)
{   
    sf::Uint32 value = std::stoul(hex, nullptr, 16);
    return sf::Color(value*256+255);
}

std::ostream& operator<<(std::ostream& os, const sf::Color& color)
{
    return os
        << "#" << std::hex << std::setw(6) << std::setfill('0')
        << color.toInteger()/256
        << std::dec << std::setfill(' ');
}