#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<cstdlib> 
#include<algorithm>
#include<SFML/System/Clock.hpp>

int main(int argc, char *argv[])
{
    int width;
    int height;
    switch(argc)
    {
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
    srand(time(NULL));
//     for(int y = 0;y<height;y++){
//         for(int x = 0;x<width;x++)
//         {
//             game_board_1[x][y]=(std::rand()%30)%2;
//             game_board_2[x][y]=game_board_1[x][y];
//         }
//     }
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            game_board_1[x][y]=0;
            game_board_2[x][y]=0;
        }
    }
    game_board_1[5][5]=1;
    game_board_2[5][5]=1;
    game_board_1[5][6]=1;
    game_board_2[5][6]=1;
    game_board_1[6][5]=1;
    game_board_2[6][5]=1;
    game_board_1[6][6]=1;
    game_board_2[6][6]=1;
    int block_size=std::min(sf::VideoMode::getDesktopMode().width/width,sf::VideoMode::getDesktopMode().height/height);
    sf::RectangleShape block(sf::Vector2f(block_size,block_size));
    sf::Clock clock;
    window.clear(sf::Color(150, 150, 150));
    for(int y = 0;y<height;y++){
        for(int x = 0;x<width;x++)
        {
            block.setPosition(x*block_size,y*block_size);
            if(game_board_1[x][y]) block.setFillColor(sf::Color::White);
            else block.setFillColor(sf::Color::Black);
            window.draw(block);
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
        if(clock.getElapsedTime().asMilliseconds()>=500)
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
                            if(i>=0&&i<width&&j>=0&&j<height&&i!=x&&j!=y)
                            {
                                if(game_board_1[i][j])
                                    living_neighbours++;
                            }
                        }
                    }
                    if(living_neighbours==3&&!game_board_1[x][y])
                        game_board_2[x][y]=true;
                    if(living_neighbours!=2&&living_neighbours!=3&&game_board_1[x][y])
                        game_board_2[x][y]=false;
                }
            }
            for(int y = 0;y<height;y++)
                for(int x = 0;x<width;x++)
                    game_board_1[x][y]=game_board_2[x][y];
                
            window.clear(sf::Color(150, 150, 150));
            for(int y = 0;y<height;y++){
                for(int x = 0;x<width;x++)
                {
                    block.setPosition(x*block_size,y*block_size);
                    if(game_board_1[x][y]) block.setFillColor(sf::Color::White);
                    else block.setFillColor(sf::Color::Black);
                    window.draw(block);
                }
            }
            window.display();
        }
    }
    return 0;
}
