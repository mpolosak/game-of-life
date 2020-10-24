#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<cstdlib> 
#include<algorithm>
#include<SFML/System/Clock.hpp>
#include<regex>

bool **game_board_1;
bool **game_board_2;
sf::RenderWindow window;
int block_size;
sf::RectangleShape block;
sf::RectangleShape board_shape;
int width;
int height;

void show_board()
{
    window.clear(sf::Color(150, 150, 150));
    window.draw(board_shape);
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            if(game_board_1[x][y])
            {
                block.setPosition(x*block_size,y*block_size);
                window.draw(block);
            }
        }
    }
    window.display();
}

bool vector_contains(std::vector<int> vector, int searched_num)
{
    for(int num:vector)
        if(searched_num==num)
            return true;
    return false;
}

void clear_board()
{
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            game_board_1[x][y]=0;
            game_board_2[x][y]=0;
        }
    }
}

void set_hovered_block_value(bool value)
{
    sf::Vector2i position = sf::Mouse::getPosition();
    int positionX = position.x/block_size;
    int positionY = position.y/block_size;
    game_board_1[positionX][positionY]=value;
    game_board_2[positionX][positionY]=value;
    show_board();
}

void draw_board()
{
    window.clear(sf::Color(150, 150, 150));
    clear_board();
    window.draw(board_shape);
    window.display();
    while(true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            set_hovered_block_value(true);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            set_hovered_block_value(false);
        sf::Event event;
        if (window.pollEvent(event)&&(event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
            break;
    }
}

void create_random_board()
{
    srand(time(NULL));
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            game_board_1[x][y]=(std::rand()%30)%2;
            game_board_2[x][y]=game_board_1[x][y];
        }
    }
}

int main(int argc, char *argv[])
{
    std::vector<int> survive = {2,3};
    std::vector<int> birth = {3};
    bool draw=false;
    switch(argc)
    {
        case 5:
        {
            std::string string=argv[4];
            if(string=="true")
                draw=true;
        }
        case 4:
        {
            std::string type_string=argv[3];
            std::smatch base_match;
            const std::regex base_regex("([0-9]*)/([0-9]*)");
            if(std::regex_match(type_string, base_match, base_regex))
            {
                std::string survive_string=base_match[1];
                std::string birth_string=base_match[2];
                
                survive={};
                for(char num:survive_string)
                    survive.push_back(std::atoi(&num));

                birth={};
                for(char num:birth_string)
                    birth.push_back(std::atoi(&num));
            }
        }
        case 3:
        {
            std::string width_string, height_string;
            width_string=argv[1];
            height_string=argv[2];
            try
            {
                width=std::stoi(width_string);
                height=std::stoi(height_string);
                break;
            }
            catch(std::logic_error)
            {
                std::cout<<"1st and 2nd arguments should be numbers"<<std::endl;
            }
        }
        default:
            width=50;
            height=50;
            std::cout<<"Size of game board will be default:"<<width<<"x"<<height<<std::endl;
    }
    game_board_1=new bool*[width];
    for(int x = 0;x<width;x++)
    {
        game_board_1[x] = new bool[height];
    }
    game_board_2=new bool*[width];
    for(int x = 0;x<width;x++)
    {
        game_board_2[x] = new bool[height];
    }
    window.create(sf::VideoMode::getDesktopMode(),"Game in life",sf::Style::Fullscreen);
    block_size=std::min(sf::VideoMode::getDesktopMode().width/width,sf::VideoMode::getDesktopMode().height/height);
    block = sf::RectangleShape(sf::Vector2f(block_size,block_size));
    block.setFillColor(sf::Color::White);
    board_shape= sf::RectangleShape(sf::Vector2f(block_size*width,block_size*height));
    board_shape.setFillColor(sf::Color::Black);
    if(draw)
        draw_board();
    else
        create_random_board();
    
    sf::Clock clock;
    show_board();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        if(clock.getElapsedTime().asMilliseconds()>=250)
        {
            clock.restart();
            for(int y = 0;y<height;y++){
                for(int x = 0;x<width;x++)
                {
                    int living_neighbours=0;
                    for(int j=y-1;j<=y+1;j++)
                    {
                        for(int i=x-1;i<=x+1;i++)
                        {
                            if(i>=0&&i<width&&j>=0&&j<height&&!(i==x&&j==y))
                            {
                                if(game_board_1[i][j])
                                    living_neighbours++;
                            }
                        }
                    }
                    switch(game_board_1[x][y])
                    {
                        case true:
                            if(!vector_contains(survive,living_neighbours))
                                game_board_2[x][y]=false;
                            break;
                        case false:
                            if(vector_contains(birth,living_neighbours))
                                game_board_2[x][y]=true;
                            break;
                    }
                }
            }
            for(int y = 0;y<height;y++)
                for(int x = 0;x<width;x++)
                    game_board_1[x][y]=game_board_2[x][y];
                
            show_board();
        }
    }
    return 0;
}
