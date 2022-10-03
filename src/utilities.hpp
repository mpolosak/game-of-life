#pragma once
#include<regex>
#include<string>
#include<utility>
#include<SFML/Graphics.hpp>

std::smatch match(
    const std::string &string, const std::string &regex);

std::pair<unsigned int,unsigned int> parseSize(const std::string &size);

bool isImage(const std::string &path);

sf::Color colorFromHex(std::string& color);

std::ostream& operator<<(std::ostream& os, const sf::Color& color);