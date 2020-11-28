#include<SFML/Graphics.hpp>
#include<unordered_set>
#include"boardconfig.hpp"

class Board
: public sf::Drawable
{
public:
    Board(BoardConfig &config);
    ~Board();
    void clear();
    void setBlockValue(int x, int y, bool value);
    void setBlockSize(unsigned int size);
    void step();
    unsigned int getWidth(){return config.width;};
    unsigned int getHeight(){return config.height;};
    unsigned int getBlockSize(){return blockSize;};
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    BoardConfig config;
    int blockSize;
    bool **gameBoard1;
    bool **gameBoard2;
    sf::RectangleShape background;
    sf::RectangleShape block;
    void fillWithRandomValues();
    int countLivingNeighbours(int x, int y);
};