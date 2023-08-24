#include"config.hpp"
#include"board.hpp"
#include"background.hpp"

class GameOfLife {
public:
    GameOfLife(int argc, char *argv[]);
    void run();
private: 
    void setFullscreen(bool);
    void processEvents();
    void handleEvent(sf::Event &event);
    void draw();
    void setViewSize(int width, int height);
    void handleKeyPress(sf::Keyboard::Key key);
    void toggleFullscreen();
    void processDrawMode();
    void setHoveredBlockValue(bool value);
    Config config;
    std::unique_ptr<Board> board;
    std::unique_ptr<Background> background;
    int style = sf::Style::Default;
    sf::RenderWindow window;
    sf::View view;
};