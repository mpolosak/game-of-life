#include<unordered_set>
#include<string>
#include<iostream>
#include<iomanip>

struct Config
{
    static Config fromCommandLine(int argc, char *argv[]);
    bool draw;
    std::unordered_set<char> survive;
    std::unordered_set<char> birth;
    unsigned int width;
    unsigned int height;
    unsigned int minBlockSize;
    bool fullscreen;
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::string rules_string;
};

std::ostream& operator<<(std::ostream& os, const Config& config);

Config parseComandLine(int argc, char *argv[]);
std::pair<std::unordered_set<char>, std::unordered_set<char>> parseRules(const std::string &rules);
std::pair<unsigned int,unsigned int> parseSize(const std::string &size);
