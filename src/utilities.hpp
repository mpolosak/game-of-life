#pragma once
#include<regex>
#include<string>
#include<utility>
#include <png++/png.hpp>
#include<SFML/Graphics.hpp>
std::smatch match(
    const std::string &string, const std::string &regex);

std::pair<unsigned int,unsigned int> parseSize(const std::string &size);

bool isPNGImage(std::string &path);

bool operator==(png::rgb_pixel pixel1, png::rgb_pixel pixel2);

sf::Color colorFromHex(std::string& color);

std::ostream& operator<<(std::ostream& os, const sf::Color& color);