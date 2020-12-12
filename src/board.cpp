#include"board.hpp"
#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>

Board::Board(BoardConfig *config)
{
    this->config = config;
    
    if(config->inputFilePath!="")
        loadFromFile();
    else if(config->draw)
    {
        initGameBoardTables();
        clear();
    }
    else
    {
        initGameBoardTables();
        fillWithRandomValues();
    }

    background.setFillColor(sf::Color::Black);
    block.setFillColor(sf::Color::White);
}

Board::~Board()
{
    if(config->outputFilePath!="")
        saveToFile();
    for(int x = 0;x<config->width;x++)
    {
        delete gameBoard1[x];
        delete gameBoard2[x];
    }
    delete gameBoard1;
    delete gameBoard2;
}

void Board::clear()
{
    for(int y = 0;y<config->height;y++)
        for(int x = 0;x<config->width;x++)
            setBlockValue(x, y, false);
}

void Board::fillWithRandomValues()
{
    srand(time(NULL));
    for(int y = 0;y<config->height;y++)
        for(int x = 0;x<config->width;x++)
            setBlockValue(x,y, (std::rand()%30)%2==1);
}

void Board::setBlockValue(int x, int y, bool value)
{
    if(x<0||y<0||x>=config->width||y>=config->height)
        return;
    gameBoard1[x][y]=value;
    gameBoard2[x][y]=value;
}

void Board::setBlockSize(unsigned int size)
{
    blockSize=std::max(size,config->minBlockSize);
    block = sf::RectangleShape(sf::Vector2f(blockSize,blockSize));
    background.setSize(sf::Vector2f(blockSize*config->width,blockSize*config->height));
}

void Board::step()
{
    for(int y = 0;y<config->height;y++)
        for(int x = 0;x<config->width;x++)
            processCell(x, y);

    equalizeTables();
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape block = this->block;
    target.draw(background);
    for(int y = 0;y<config->height;y++){
        for(int x = 0;x<config->width;x++)
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
    gameBoard1 = new bool*[config->width];
    gameBoard2 = new bool*[config->width];
    for(int x = 0;x<config->width;x++)
    {
        gameBoard1[x] = new bool[config->height];
        gameBoard2[x] = new bool[config->height];
    }
}

void Board::loadFromFile()
{
    std::fstream file(config->inputFilePath, std::ios::in);
    if(!file)
        throw std::string("Failed to open file "+config->inputFilePath);
    
    file>>*this;

    file.close();
}

void Board::saveToFile()
{
    std::fstream file(config->outputFilePath, std::ios::out);
    if(!file)
        std::cerr << "Failed to save to file " << config->outputFilePath << std::endl;
    
    file<<*this;

    file.close();
}

int Board::countLivingNeighbours(int x, int y)
{
    int livingNeighbours=0;

    for(int j=y-1;j<=y+1;j++)
        for(int i=x-1;i<=x+1;i++)
            if(i>=0&&i<config->width&&j>=0&&j<config->height&&!(i==x&&j==y))
                if(gameBoard1[i][j])
                    livingNeighbours++;

    return livingNeighbours;
}

void Board::processCell(int x, int y)
{
    if(gameBoard1[x][y])
    {
        if(!config->survive.count(countLivingNeighbours(x,y)))
            gameBoard2[x][y]=false;
    }
    else
    {
        if(config->birth.count(countLivingNeighbours(x,y)))
            gameBoard2[x][y]=true;
    }
}

void Board::equalizeTables()
{
    for(int y = 0;y<config->height;y++)
        for(int x = 0;x<config->width;x++)
            gameBoard1[x][y]=gameBoard2[x][y];
}

void Board::setBlockValue(int x, int y, char value)
{
    switch(value)
    {
        case 'X':
            setBlockValue(x, y, true);
            break;
        case ' ':
            setBlockValue(x, y, false);
            break;
        default:
            throw "The board file should only contain 'X's and spaces";
            break;
    }
}

std::fstream& operator<<(std::fstream& os, const Board& board)
{
    for(int y = 0;y<board.config->height;y++)
    {
        for(int x = 0; x<board.config->width; x++)
        {
            if(board.gameBoard1[x][y])
                os<<'X';
            else
                os<<' ';
        }
        if(y!=(board.config->height-1))
            os<<"\n";
    }
    return os;
}

void operator>>(std::fstream& fs, Board& board)
{
    std::vector<std::string> lines = loadNonEmptyLines(fs);

    board.config->width = lines[0].length();
    board.config->height = lines.size();

    board.initGameBoardTables();

    for(int y=0; y<board.config->height; y++)
    {
        std::string line = lines[y];
        if(line.length()!=board.config->width)
            throw std::string("All lines in the board file must be the same lenght");
        for(int x=0; x<board.config->width; x++)
            board.setBlockValue(x, y, line[x]);
    }
}

std::vector<std::string> loadNonEmptyLines(std::fstream& fs)
{
    std::vector<std::string> lines;
    std::string line;
    while(getline(fs, line))
        lines.push_back(line);

    if(lines.empty())
        throw std::string("The board file is empty");
    else if(line.empty())
        throw std::string("The board file contains an empty line");

    return lines;
}