#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "boardconfig.hpp"
#include "appearanceconfig.hpp"
#include <memory>

class Board
    : public sf::Drawable
{
public:
    Board(BoardConfig *config, AppearanceConfig &appearance);
    ~Board();
    void clear();
    void step();
    void setBlockOnPos(sf::Vector2u position, bool value);
    void handleNewViewSize(int width, int height);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    BoardConfig *config;
    BoardPosition position;
    unsigned blockSize;
    std::unique_ptr<bool[]> gameBoard1;
    std::unique_ptr<bool[]> gameBoard2;
    sf::RectangleShape background;
    sf::RectangleShape block;
    sf::Vector2u offset = {0, 0};
    void initGameBoardArrays();
    void fillWithRandomValues();
    void loadFromFile();
    void loadFromImage();
    void loadFromTextFile();
    void saveToFile();
    void saveToImage();
    void saveToTextFile();
    int countLivingNeighbours(unsigned x, unsigned y);
    void processCell(int x, int y);
    void swapArrays();
    void setBlockValue(sf::Vector2u cords, bool value);
    void setBlockValue(sf::Vector2u cords, char value);
    void setBlockValue(sf::Vector2u cords, sf::Color value);
    void setBlockSize(unsigned int size);
    friend std::fstream &operator<<(std::fstream &os, const Board &board);
    friend void operator>>(std::fstream &fs, Board &board);
};

std::fstream &operator<<(std::fstream &os, const Board &board);
void operator>>(std::fstream &fs, Board &board);

std::vector<std::string> loadNonEmptyLines(std::fstream &fs);