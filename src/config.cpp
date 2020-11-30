#include"config.hpp"
#include"utilities.hpp"
#include<boost/program_options.hpp>
#include<iomanip>

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
        ("load,l", po::value<std::string>(&config.board.inputFilePath), "load board from file arg")
        ("save,S", po::value<std::string>(&config.board.outputFilePath), "save the board to file arg")
        ("draw,d", "use mouse to draw a board")
        ("rules,r", po::value<std::string>(&rulesString)->default_value("23/3"), "set rules to arg, the rules must be written as survive/birth i.e. 123/45)")
        ("size,s", po::value<std::string>(&boardSize)->default_value("50x50"), "set size of board to arg, the size must be written as widthxheight i.e. 192x108")
        ("block_size,b", po::value<unsigned int>(&config.board.minBlockSize)->default_value(1), "set minimal size of block to arg")
        ("fullscreen,f", "run in fullscreen mode")
        ("window_size,w", po::value<std::string>(&windowSize)->default_value("500x500"), "set size of window to arg, the size must be written as widthxheight i.e. 800x600")
    ;
    po::variables_map vm;

    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);   
        po::notify(vm);
    }
    catch(std::logic_error &error)
    {
        throw std::string(error.what())+"\nType in 'game-of-life -h' to get help";
    }

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        throw 0;
    }

    try{
        config.board.setRules(rulesString);
        config.board.setSize(boardSize);
        config.setSize(windowSize);
    }
    catch(...)
    {
        throw;
    }

    config.board.draw = vm.count("draw");

    config.fullscreen=vm.count("fullscreen");

    return config;
}

std::ostream& operator<<(std::ostream& os, const Config& config)
{
    return os << std::boolalpha
        << config.board
        << std::setw(20) << "Window size" << " : " 
            << config.width << "x" << config.height << std::endl
        << std::setw(20) << "Fullscreen" << " : " << config.fullscreen << std::endl;
}

void Config::setSize(const std::string &size)
{
    auto sizePair = parseSize(size);
    width=sizePair.first;
    height=sizePair.second;
}
