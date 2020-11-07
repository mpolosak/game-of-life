#include<unordered_set>
#include<string>
#include<iostream>
#include<iomanip>

class Config
{
public:
    static Config fromCommandLine(int argc, char *argv[]);
    void setRules(const std::string &rulesString);
    std::string getRules()const{return rulesString;};
    void setBoardSize(const std::string &size);
    void setWindowSize(const std::string &size);
    bool draw;
    std::unordered_set<char> survive;
    std::unordered_set<char> birth;
    unsigned int width;
    unsigned int height;
    unsigned int minBlockSize;
    bool fullscreen;
    unsigned int windowWidth;
    unsigned int windowHeight;
private:
    std::string rulesString;
};

std::ostream& operator<<(std::ostream& os, const Config& config);

std::pair<unsigned int,unsigned int> parseSize(const std::string &size);
