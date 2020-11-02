#include"board.hpp"
#include<algorithm>
#include<iostream>

Board::Board(unsigned int width, unsigned int height,
    unsigned int minBlockSize)
{
    this->width=width;
    this->height=height;
    gameBoard1=new bool*[width];
    gameBoard2=new bool*[width];
    for(int x = 0;x<width;x++)
    {
        gameBoard1[x] = new bool[height];
        gameBoard2[x] = new bool[height];
    }
    background.setFillColor(sf::Color::Black);
    block.setFillColor(sf::Color::White);
    this->minBlockSize=minBlockSize;
}

Board::~Board()
{
    for(int x = 0;x<width;x++)
    {
        delete gameBoard1[x];
        delete gameBoard2[x];
    }
    delete gameBoard1;
    delete gameBoard2;
}

void Board::clear()
{
    for(int y = 0;y<height;y++)
        for(int x = 0;x<width;x++)
            setBlockValue(x, y, false);
}

void Board::fillWithRandomValues()
{
    srand(time(NULL));
    for(int y = 0;y<height;y++)
        for(int x = 0;x<width;x++)
            setBlockValue(x,y, (std::rand()%30)%2);
}

void Board::setBlockValue(int x, int y, bool value)
{
    if(x<0||y<0||x>=width||y>=height)
        return;
    gameBoard1[x][y]=value;
    gameBoard2[x][y]=value;
}

void Board::setBlockSize(unsigned int size)
{
    blockSize=std::max(size,minBlockSize);
    block = sf::RectangleShape(sf::Vector2f(blockSize,blockSize));
    background.setSize(sf::Vector2f(blockSize*width,blockSize*height));
}

void Board::step()
{
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            if(gameBoard1[x][y])
                if(!survive.count(countLivingNeighbours(x,y)))
                    gameBoard2[x][y]=false;
            else
                if(birth.count(countLivingNeighbours(x,y)))
                    gameBoard2[x][y]=true;

        }
    }
    for(int y = 0;y<height;y++)
        for(int x = 0;x<width;x++)
            gameBoard1[x][y]=gameBoard2[x][y];
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape block = this->block;
    target.draw(background);
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            if(gameBoard1[x][y])
            {
                block.setPosition(x*blockSize,y*blockSize);
                target.draw(block);
            }
        }
    }
}

int Board::countLivingNeighbours(int x, int y)
{
    int livingNeighbours=0;

    for(int j=y-1;j<=y+1;j++)
        for(int i=x-1;i<=x+1;i++)
            if(i>=0&&i<width&&j>=0&&j<height&&!(i==x&&j==y))
                if(gameBoard1[i][j])
                    livingNeighbours++;

    return livingNeighbours;
}