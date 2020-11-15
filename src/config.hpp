#include<iostream>
#include"boardconfig.hpp"

class Config
{
public:
    static Config fromCommandLine(int argc, char *argv[]);
    void setSize(const std::string &size);
    bool draw;
    bool fullscreen;
    unsigned int width;
    unsigned int height; 
    BoardConfig board;
};

std::ostream& operator<<(std::ostream& os, const Config& config);
