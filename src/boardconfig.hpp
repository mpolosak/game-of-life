#pragma once
#include<string>
#include<unordered_set>

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
private:
    std::string rulesString;
};

std::ostream& operator<<(std::ostream& os, const BoardConfig& config);