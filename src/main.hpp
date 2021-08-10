#include <SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include"board.hpp"
#include"config.hpp"

void init(int argc, char *argv[]);
void run();
void processEvents();
void setViewSize(int width, int height);
void draw();
void handleEvent(sf::Event &event);
void handleKeyPress(sf::Keyboard::Key key);
void setHoveredBlockValue(bool value);
void processDrawMode();
void setFullscreen(bool fullscreen);
void toggleFullscreen();
void loadBackground();
void setBackgroundSize(int width, int height);