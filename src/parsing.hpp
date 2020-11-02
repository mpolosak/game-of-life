#include<unordered_set>
#include<string>

struct Config
{
    bool draw;
    std::unordered_set<char> survive;
    std::unordered_set<char> birth;
    unsigned int width;
    unsigned int height;
    unsigned int minBlockSize;
    bool fullscreen;
};

Config parseComandLine(int argc, char *argv[]);
std::pair<std::unordered_set<char>, std::unordered_set<char>> parseRules(const std::string &rules);
std::pair<unsigned int,unsigned int> parseSize(const std::string &size);