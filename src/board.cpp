#include"board.hpp"
#include"utilities.hpp"
#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<random>

Board::Board(BoardConfig *config, AppearanceConfig& appearance)
{
    this->config = config;
    
    if(config->inputFilePath!="")
        loadFromFile();
    else if(config->draw)
    {
        initGameBoardArrays();
        clear();
    }
    else
    {
        initGameBoardArrays();
        fillWithRandomValues();
    }

    background.setFillColor(appearance.deadCellColor);
    block.setFillColor(appearance.liveCellColor);
    position = appearance.boardPosition;
}

Board::~Board()
{
    if(config->outputFilePath!="")
        saveToFile();
}

void Board::clear()
{
    for(uint y = 0;y<config->height;y++)
        for(uint x = 0;x<config->width;x++)
            setBlockValue({x, y}, false);
}

void Board::fillWithRandomValues()
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(0, 1);
    for(uint y = 0;y<config->height;y++)
        for(uint x = 0;x<config->width;x++)
            setBlockValue({x,y}, (bool) uniform_dist(e1));
}

void Board::step()
{
    for(uint y = 0;y<config->height;y++)
        for(uint x = 0;x<config->width;x++)
            processCell(x, y);

    equalizeArrays();
}

void Board::setBlockOnPos(sf::Vector2u position, bool value)
{
    auto cords = (position-sf::Vector2u(offset))/blockSize;
    setBlockValue(cords, value);
}

void Board::handleNewViewSize(int width, int height)
{
    setBlockSize(std::min(width/config->width,height/config->height));
    switch(position){
        case BoardPosition::topleft:
            break;
        case BoardPosition::top:
            offset = {(width-config->width*blockSize)/2, 0};
            break;
        case BoardPosition::topright:
            offset = {width-config->width*blockSize, 0};
            break;
        case BoardPosition::right:
            offset = {width-config->width*blockSize, (height-config->height*blockSize)/2};
            break;
        case BoardPosition::bottomright:
            offset = {width-config->width*blockSize, height-config->height*blockSize};
            break;
        case BoardPosition::bottom:
            offset = {(width-config->width*blockSize)/2, height-config->height*blockSize};
            break;
        case BoardPosition::bottomleft:
            offset = {0, height-config->height*blockSize};
            break;
        case BoardPosition::left:
            offset = {0, (height-config->height*blockSize)/2};
            break;
        case BoardPosition::center:
            offset = {(width-config->width*blockSize)/2, (height-config->height*blockSize)/2};
            break;
    }
    background.setPosition(offset);
}


void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::RectangleShape block = this->block;
    target.draw(background);
    auto pos = offset;
    for(uint y = 0;y<config->height;y++){
        for(uint x = 0;x<config->width;x++)
        {
            if(gameBoard1[x+y*config->width])
            {
                block.setPosition(pos);
                target.draw(block);
            }
            pos.x+=blockSize;
        }
        pos.y+=blockSize;
        pos.x=offset.x;
    }
}

void Board::initGameBoardArrays()
{
    int arraysSize = config->width*config->height;
    gameBoard1 = std::make_unique<bool[]>(arraysSize);
    gameBoard2 = std::make_unique<bool[]>(arraysSize);
}

void Board::loadFromFile()
{
    if(isImage(config->inputFilePath))
        loadFromImage();
    else{
        loadFromTextFile();
    }
}

void Board::loadFromImage()
{
    sf::Image image;
    if(!image.loadFromFile(config->inputFilePath)) 
        std::exit(1);
    const auto size = image.getSize();
    config->width = size.x;
    config->height = size.y;
    initGameBoardArrays();
    for(uint x=0; x<config->width; x++)
        for(uint y=0; y<config->height; y++)
            setBlockValue({x, y}, image.getPixel(x,y));
}

void Board::loadFromTextFile()
{
    std::fstream file(config->inputFilePath, std::ios::in);
    if(!file)
        throw std::string("Failed to open file '"+config->inputFilePath+"'");
    
    file>>*this;

    file.close();
}

void Board::saveToFile()
{
    if(isImage(config->outputFilePath))
        saveToImage();
    else
        saveToTextFile();
}

void Board::saveToImage()
{
    sf::Image image;
    image.create(config->width, config->height, sf::Color::Black);
    for(uint x=0; x<config->width; x++)
        for(uint y=0; y<config->height; y++)
            if(gameBoard1[x+y*config->width])
                image.setPixel(x, y, sf::Color::White);
    
    image.saveToFile(config->outputFilePath);
}

void Board::saveToTextFile()
{
    std::fstream file(config->outputFilePath, std::ios::out);
    if(!file)
        std::cerr << "Failed to save to file '" << config->outputFilePath << "'" << std::endl;
    
    file<<*this;

    file.close();
}

int Board::countLivingNeighbours(uint x, uint y)
{
    int livingNeighbours=0;

    for(uint j=y-1;j<=y+1;j++)
        for(uint i=x-1;i<=x+1;i++)
            if(i>=0&&i<config->width&&j>=0&&j<config->height&&!(i==x&&j==y))
                if(gameBoard1[i+j*config->width])
                    livingNeighbours++;

    return livingNeighbours;
}

void Board::processCell(int x, int y)
{
    if(gameBoard1[x+y*config->width])
    {
        if(!config->survive.count(countLivingNeighbours(x,y)))
            gameBoard2[x+y*config->width]=false;
    }
    else
    {
        if(config->birth.count(countLivingNeighbours(x,y)))
            gameBoard2[x+y*config->width]=true;
    }
}

void Board::equalizeArrays()
{
    uint arraysSize = config->height*config->width; 
    for(uint i = 0; i<arraysSize; i++)
        gameBoard1[i]=gameBoard2[i];
}

void Board::setBlockValue(sf::Vector2u cords, bool value)
{
    auto [x, y] = cords;
    if(x>=config->width||y>=config->height)
        return;
    gameBoard1[x+y*config->width]=value;
    gameBoard2[x+y*config->width]=value;
}

void Board::setBlockValue(sf::Vector2u cords, char value)
{
    switch(value)
    {
        case 'X':
            setBlockValue(cords, true);
            break;
        case ' ':
            setBlockValue(cords, false);
            break;
        default:
            throw "The board file should only contain 'X's and spaces";
            break;
    }
}

void Board::setBlockValue(sf::Vector2u cords, sf::Color value)
{
    if(value==sf::Color::White)
        setBlockValue(cords, true);
    else if (value==sf::Color::Black)
        setBlockValue(cords, false);
    else
        throw std::string("The board image should contain only black and white pixels");
}

void Board::setBlockSize(unsigned int size)
{
    blockSize=std::max(size,config->minBlockSize);
    block.setSize(sf::Vector2f(blockSize,blockSize));
    background.setSize(sf::Vector2f(blockSize*config->width,blockSize*config->height));
}

std::fstream& operator<<(std::fstream& os, const Board& board)
{
    for(uint y = 0;y<board.config->height;y++)
    {
        for(uint x = 0; x<board.config->width; x++)
        {
            if(board.gameBoard1[x+y*board.config->width])
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

    board.initGameBoardArrays();

    for(uint y=0; y<board.config->height; y++)
    {
        std::string line = lines[y];
        if(line.length()!=board.config->width)
            throw std::string("All lines in the board file must be the same lenght");
        for(uint x=0; x<board.config->width; x++)
            board.setBlockValue({x, y}, line[x]);
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