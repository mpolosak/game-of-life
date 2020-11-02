#include<SFML/Graphics.hpp>
#include<unordered_set>

class Board
: public sf::Drawable
{
public:
    Board(unsigned int width, unsigned int height,
        unsigned int minBlockSize);
    ~Board();
    void clear();
    void fillWithRandomValues();
    void setBlockValue(int x, int y, bool value);
    void setBlockSize(unsigned int size);
    void step();
    unsigned int getWidth(){return width;};
    unsigned int getHeight(){return height;};
    unsigned int getBlockSize(){return blockSize;};
    std::unordered_set<char> survive;
    std::unordered_set<char> birth;
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    bool **gameBoard1;
    bool **gameBoard2;
    sf::RectangleShape background;
    sf::RectangleShape block;
    unsigned int blockSize;
    unsigned int minBlockSize;
    unsigned int width;
    unsigned int height;
    int countLivingNeighbours(int x, int y);
};