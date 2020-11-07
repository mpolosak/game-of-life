#include "parsing.hpp"
#include<boost/program_options.hpp>
#include<regex>

namespace po = boost::program_options;

Config Config::fromCommandLine(int argc, char *argv[])
{
    Config config;
    std::string rulesString;
    std::string boardSize;
    std::string windowSize;

    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "show this description and return")
        ("draw,d", "use mouse to draw a board, if not present the board is filled randomly")
        ("rules,r", po::value<std::string>(&rulesString)->default_value("23/3"), "set rules to arg, the rules must be written as survive/birth i.e. 123/45)")
        ("size,s", po::value<std::string>(&boardSize)->default_value("50x50"), "set size of board to arg, the size must be written as widthxheight i.e. 192x108")
        ("block_size,b", po::value<unsigned int>(&config.minBlockSize)->default_value(1), "set minimal size of block to arg")
        ("fullscreen,f", "run in fullscreen mode")
        ("window_size,w", po::value<std::string>(&windowSize)->default_value("500x500"), "set size of window to arg, the size must be written as widthxheight i.e. 800x600")
    ;
    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);   
        po::notify(vm);
    }
    catch(boost::wrapexcept<po::unknown_option> &error)
    {
        std::string error_string=error.get_option_name() + " isn't correct option\n"
            + "Type in 'game-of-live -h' to get list of allowed options";
        throw error_string;
    }
    catch(boost::wrapexcept<po::invalid_command_line_syntax> &error)
    {
        throw std::string("Invalid syntax\nType in 'game-of-live -h' to get help");
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        throw 0;
    }

    try{
        config.setRules(rulesString);
        config.setBoardSize(boardSize);
        config.setWindowSize(windowSize);
    }
    catch(...)
    {
        throw;
    }

    config.draw=vm.count("draw");
    config.fullscreen=vm.count("fullscreen");

    return config;
}

std::ostream& operator<<(std::ostream& os, const Config& config)
{
    return os << std::boolalpha
        << std::setw(20) << "Draw board" << " : " << config.draw << std::endl
        << std::setw(20) << "Rules" << " : " << config.getRules() << std::endl
        << std::setw(20) << "Minimum block size" << " : " 
            << config.minBlockSize << std::endl
        << std::setw(20) << "Board size" << " : " 
            << config.width << "x" << config.height<< std::endl
        << std::setw(20) << "Window size" << " : " 
            << config.windowWidth << "x" << config.windowHeight << std::endl
        << std::setw(20) << "Fullscreen" << " : " << config.fullscreen << std::endl;
}

void Config::setRules(const std::string &rulesString)
{
    std::smatch base_match;
    const std::regex base_regex("([0-9]*)/([0-9]*)");
    if(std::regex_match(rulesString, base_match, base_regex))
    {
        this->rulesString=rulesString;
        std::string survive_string=base_match[1];
        std::string birth_string=base_match[2];
        
        for(char num:survive_string)
            survive.insert(std::atoi(&num));

        for(char num:birth_string)
            birth.insert(std::atoi(&num));

    }
    else
        throw std::string("Rules must be written as survive/birth i.e. 123/45");
}

void Config::setBoardSize(const std::string &size)
{
    auto sizePair = parseSize(size);
    width=sizePair.first;
    height=sizePair.second;
}

void Config::setWindowSize(const std::string &size)
{
    auto sizePair = parseSize(size);
    windowWidth=sizePair.first;
    windowHeight=sizePair.second;
}

std::pair<unsigned int,unsigned int> parseSize(const std::string &size)
{
    unsigned int width;
    unsigned int height;
    std::smatch base_match;
    const std::regex base_regex("([0-9]*)x([0-9]*)");
    if(std::regex_match(size, base_match, base_regex))
    {
        std::string width_string=base_match[1];
        std::string height_string=base_match[2];

        width = std::stoi(width_string);
        height = std::stoi(height_string);
        if(width==0||height==0)
        {
            throw std::string("Neither height nor width cannot be equal to zero");
        }
    }
    else
        throw std::string("The size must be written as widthxheight i.e. 192x108");
    
    return std::make_pair(width,height); 
}
