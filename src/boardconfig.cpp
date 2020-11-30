#include"boardconfig.hpp"
#include"utilities.hpp"
#include<iomanip>

void BoardConfig::setRules(const std::string &rulesString)
{
    this->rulesString = rulesString;

    std::smatch base_match;
    try{
        base_match = match(rulesString, "([0-9]*)/([0-9]*)");
    }
    catch(...)
    {
        throw std::string("Rules must be written as survive/birth i.e. 123/45");
    }
    
    std::string survive_string = base_match[0];
    std::string birth_string = base_match[0];

    for(char num:survive_string)
        survive.insert(std::atoi(&num));

    for(char num:birth_string)
        birth.insert(std::atoi(&num));

}

void BoardConfig::setSize(const std::string &size)
{
    auto sizePair = parseSize(size);
    width=sizePair.first;
    height=sizePair.second;
}

std::ostream& operator<<(std::ostream& os, const BoardConfig& config)
{
    return os
        << std::setw(20) << "Rules" << " : " << config.getRules() << std::endl
        << std::setw(20) << "Load from file" << " : "
            << (config.inputFilePath!="" ? config.inputFilePath : "no") << std::endl
        << std::setw(20) << "Save to file" << " : "
            << (config.outputFilePath!="" ? config.outputFilePath : "no") << std::endl
        << std::setw(20) << "Draw" << " : "
            << (config.draw ? "yes" : "no") << std::endl
        << std::setw(20) << "Board size" << " : " 
            << config.width << "x" << config.height<< std::endl
        << std::setw(20) << "Minimum block size" << " : " 
            << config.minBlockSize << std::endl;
}