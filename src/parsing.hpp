#include<unordered_set>
#include<string>
#include<iostream>
#include<iomanip>

struct Config
{
    void print();
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
    
    template <typename T>
    static void printLine (const std::string &desc, const T &value)
    { 
        std::cout << std::setw(20) << desc << " : " << value << std::endl;
    }
};

Config parseComandLine(int argc, char *argv[]);
std::pair<std::unordered_set<char>, std::unordered_set<char>> parseRules(const std::string &rules);
std::pair<unsigned int,unsigned int> parseSize(const std::string &size);
