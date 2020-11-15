#include<regex>
#include<string>
#include<utility>

std::smatch match(
    const std::string &string, const std::string &regex);

std::pair<unsigned int,unsigned int> parseSize(const std::string &size);