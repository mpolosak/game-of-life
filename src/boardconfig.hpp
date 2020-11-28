#pragma once
#include<string>
#include<unordered_set>

enum BoardMethod{Random, Draw, LoadFromFile};

class BoardConfig
{
public:
    void setRules(const std::string &rulesString);
    std::string getRules()const{return rulesString;};
    void setSize(const std::string &size);
    unsigned int width;
    unsigned int height;
    std::unordered_set<char> survive;
    std::unordered_set<char> birth;
    unsigned int minBlockSize;
    BoardMethod method = Random;
    std::string path = "";
private:
    std::string rulesString;
};

std::ostream& operator<<(std::ostream& os, const BoardConfig& config);