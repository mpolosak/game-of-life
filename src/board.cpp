#include"board.hpp"
#include<algorithm>
#include<iostream>
#include<fstream>

Board::Board(BoardConfig &config)
{
    this->config = config;

    switch(config.method)
    {
        case BoardMethod::Random:
            initGameBoardTables();
            fillWithRandomValues();
            break;
        case BoardMethod::Draw:
            initGameBoardTables();
            break;
        case BoardMethod::LoadFromFile:
            try
            {
               loadFromFile();
            }
            catch(...)
            {
                throw;
            }
            break;
    }

    background.setFillColor(sf::Color::Black);
    block.setFillColor(sf::Color::White);
}

Board::~Board()
{
    for(int x = 0;x<config.width;x++)
    {
        delete gameBoard1[x];
        delete gameBoard2[x];
    }
    delete gameBoard1;
    delete gameBoard2;
}

void Board::clear()
{
    for(int y = 0;y<config.height;y++)
        for(int x = 0;x<config.width;x++)
            setBlockValue(x, y, false);
}

void Board::fillWithRandomValues()
{
    srand(time(NULL));
    for(int y = 0;y<config.height;y++)
        for(int x = 0;x<config.width;x++)
            setBlockValue(x,y, (std::rand()%30)%2);
}

void Board::setBlockValue(int x, int y, bool value)
{
    if(x<0||y<0||x>=config.width||y>=config.height)
        return;
    gameBoard1[x][y]=value;
    gameBoard2[x][y]=value;
}

void Board::setBlockSize(unsigned int size)
{
    blockSize=std::max(size,config.minBlockSize);
    block = sf::RectangleShape(sf::Vector2f(blockSize,blockSize));
    background.setSize(sf::Vector2f(blockSize*config.width,blockSize*config.height));
}

void Board::step()
{
    for(int y = 0;y<config.height;y++){
        for(int x = 0;x<config.width;x++)
        {
            if(gameBoard1[x][y])
                if(!config.survive.count(countLivingNeighbours(x,y)))
                    gameBoard2[x][y]=false;
            else
                if(config.birth.count(countLivingNeighbours(x,y)))
                    gameBoard2[x][y]=true;

        }
    }
    for(int y = 0;y<config.height;y++)
        for(int x = 0;x<config.width;x++)
            gameBoard1[x][y]=gameBoard2[x][y];
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape block = this->block;
    target.draw(background);
    for(int y = 0;y<config.height;y++){
        for(int x = 0;x<config.width;x++)
        {
            if(gameBoard1[x][y])
            {
                block.setPosition(x*blockSize,y*blockSize);
                target.draw(block);
            }
        }
    }
}

void Board::initGameBoardTables()
{
    gameBoard1 = new bool*[config.width];
    gameBoard2 = new bool*[config.width];
    for(int x = 0;x<config.width;x++)
    {
        gameBoard1[x] = new bool[config.height];
        gameBoard2[x] = new bool[config.height];
    }
}

void Board::loadFromFile()
{
    std::fstream file(config.path, std::ios::in);
    if(!file)
        throw std::string("Failed to open file "+config.path);
    file.close();
}

int Board::countLivingNeighbours(int x, int y)
{
    int livingNeighbours=0;

    for(int j=y-1;j<=y+1;j++)
        for(int i=x-1;i<=x+1;i++)
            if(i>=0&&i<config.width&&j>=0&&j<config.height&&!(i==x&&j==y))
                if(gameBoard1[i][j])
                    livingNeighbours++;

    return livingNeighbours;
}