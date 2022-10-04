#include<SFML/Graphics.hpp>
#include<unordered_set>
#include"boardconfig.hpp"
#include"appearanceconfig.hpp"
#include<memory>

class Board
: public sf::Drawable
{
public:
    Board(BoardConfig *config, AppearanceConfig& appearance);
    ~Board();
    void clear();
    void step();
    void setBlockOnPos(sf::Vector2i position, bool value);
    void handleNewViewSize(int width, int height);
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    BoardConfig *config;
    BoardPosition position;
    int blockSize;
    std::unique_ptr<bool[]> gameBoard1;
    std::unique_ptr<bool[]> gameBoard2;
    sf::RectangleShape background;
    sf::RectangleShape block;
    sf::Vector2f offset={0,0};
    void initGameBoardArrays();
    void fillWithRandomValues();
    void loadFromFile();
    void loadFromImage();
    void loadFromTextFile();
    void saveToFile();
    void saveToImage();
    void saveToTextFile();
    int countLivingNeighbours(int x, int y);
    void processCell(int x, int y);
    void equalizeArrays();
    void setBlockValue(sf::Vector2i cords, bool value);
    void setBlockValue(sf::Vector2i cords, char value);
    void setBlockValue(sf::Vector2i cords, sf::Color value);
    void setBlockSize(unsigned int size);
    friend std::fstream& operator<<(std::fstream& os, const Board& board);
    friend void operator>>(std::fstream& fs, Board& board);
};

std::fstream& operator<<(std::fstream& os, const Board& board);
void operator>>(std::fstream& fs, Board& board);

std::vector<std::string> loadNonEmptyLines(std::fstream& fs);