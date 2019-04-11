#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<cstdlib> 
#include<algorithm>
#include<SFML/System/Clock.hpp>
#include<regex>

bool vector_contains(std::vector<int> vector, int searched_num)
{
    for(int num:vector)
        if(searched_num==num)
            return true;
    return false;
}

int main(int argc, char *argv[])
{
    int width;
    int height;
    std::vector<int> survive = {3};
    std::vector<int> birth = {2,3};
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
    bool game_board_1[width][height];
    bool game_board_2[width][height];
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Game in life",sf::Style::Fullscreen);
    int block_size=std::min(sf::VideoMode::getDesktopMode().width/width,sf::VideoMode::getDesktopMode().height/height);
    sf::RectangleShape block(sf::Vector2f(block_size,block_size));
    block.setFillColor(sf::Color::White);
    sf::RectangleShape board_shape(sf::Vector2f(block_size*width,block_size*height));
    board_shape.setFillColor(sf::Color::Black);
    if(draw)
    {
        window.clear(sf::Color(150, 150, 150));
        for(int y = 0;y<height;y++){
            for(int x = 0;x<width;x++)
            {
                game_board_1[x][y]=0;
                game_board_2[x][y]=0;
            }
        }
        window.draw(board_shape);
        window.display();
        while(true)
        {
            sf::Event event;
            if (window.pollEvent(event))
            {
                if(event.type == sf::Event::MouseButtonPressed)
                {
                    if(event.mouseButton.button==sf::Mouse::Button::Left)
                    {
                        int positionX = event.mouseButton.x/block_size;
                        int positionY = event.mouseButton.y/block_size;
                        game_board_1[positionX][positionY]=1;
                        game_board_2[positionX][positionY]=1;
                    }
                    else if(event.mouseButton.button==sf::Mouse::Button::Right)
                    {
                        int positionX = event.mouseButton.x/block_size;
                        int positionY = event.mouseButton.y/block_size;
                        
                        game_board_1[positionX][positionY]=0;
                        game_board_2[positionX][positionY]=0;
                    }
                }
                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                    break;
            }
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
    }
    else
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
    
    sf::Clock clock;
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
    }
    return 0;
}
