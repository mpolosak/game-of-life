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
    void setBlockValue(int x, int y, bool value);
    void step();
    unsigned int getBlockSize(){return blockSize;};
    void handleNewViewSize(int width, int height);
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    BoardConfig *config;
    int blockSize;
    std::unique_ptr<bool[]> gameBoard1;
    std::unique_ptr<bool[]> gameBoard2;
    sf::RectangleShape background;
    sf::RectangleShape block;
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
    void setBlockValue(int x, int y, char value);
    void setBlockValue(int x, int y, png::rgb_pixel value);
    void setBlockSize(unsigned int size);
    friend std::fstream& operator<<(std::fstream& os, const Board& board);
    friend void operator>>(std::fstream& fs, Board& board);
};

std::fstream& operator<<(std::fstream& os, const Board& board);
void operator>>(std::fstream& fs, Board& board);

std::vector<std::string> loadNonEmptyLines(std::fstream& fs);