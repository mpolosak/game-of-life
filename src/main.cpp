#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include<cstdlib> 
#include<algorithm>
#include<SFML/System/Clock.hpp>
#include<regex>
#include<boost/program_options.hpp>

namespace po = boost::program_options;

bool **game_board_1;
bool **game_board_2;
sf::RenderWindow window;
int block_size;
sf::RectangleShape block;
sf::RectangleShape board_shape;
int width=50;
int height=50;
sf::VideoMode video_mode;
int style = sf::Style::Default;

void create_board()
{
    game_board_1=new bool*[width];
    game_board_2=new bool*[width];
    for(int x = 0;x<width;x++)
    {
        game_board_1[x] = new bool[height];
        game_board_2[x] = new bool[height];
    }
}

void init_shapes()
{
    block_size=std::min(video_mode.width/width,video_mode.height/height);
    block = sf::RectangleShape(sf::Vector2f(block_size,block_size));
    block.setFillColor(sf::Color::White);
    board_shape= sf::RectangleShape(sf::Vector2f(block_size*width,block_size*height));
    board_shape.setFillColor(sf::Color::Black);
}

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
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if(position.x<0||position.y<0)
        return;
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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (
                event.type == sf::Event::KeyPressed 
                && event.key.code == sf::Keyboard::Enter
            )
                return;
            else if (
                (event.type == sf::Event::KeyPressed 
                && event.key.code == sf::Keyboard::Escape)
                || event.type == sf::Event::Closed
            )
            {
                window.close();
                return;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            set_hovered_block_value(true);
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            set_hovered_block_value(false);
    }
}

void fill_board_with_random_values()
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

int count_living_neighbours(int x, int y)
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
    return living_neighbours;
}

int main(int argc, char *argv[])
{
    std::vector<int> survive = {2,3};
    std::vector<int> birth = {3};

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "show this description and return")
        ("draw,d", "use mouse to draw a board, if not present the board is filled randomly")
        ("rules,r", po::value<std::string>(), "set rules to arg, the rules must be written as survive/birth i.e. 123/45, if not present the rules are set to standard(23/3)")
        ("size,s", po::value<std::string>(), "set size of board to arg, the size must be written as widthxheight i.e. 192x108, if not present the size is set to 50x50")
        ("fullscreen,f", "run in fullscreen mode")
    ;
    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);   
        po::notify(vm);
    }
    catch(boost::wrapexcept<boost::program_options::unknown_option> &error)
    {
        std::cerr<<error.get_option_name()<<" isn't correct option"<<std::endl;
        std::cerr<<"Type in 'game-of-live -h' to get list of allowed options"<<std::endl;
        return 1;
    }
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }
    if(vm.count("rules"))
    {
        std::string rules = vm["rules"].as<std::string>();
        std::smatch base_match;
        const std::regex base_regex("([0-9]*)/([0-9]*)");
        if(std::regex_match(rules, base_match, base_regex))
        {
            std::string survive_string=base_match[1];
            std::string birth_string=base_match[2];
            
            survive={};
            for(char num:survive_string)
                survive.push_back(std::atoi(&num));

            birth={};
            for(char num:birth_string)
                birth.push_back(std::atoi(&num));
            std::cout<<"The rules set to "<<rules<<std::endl;
        }
        else{
            std::cerr<<"Rules must be written as survive/birth i.e. 123/45"<<std::endl;
            return 1;
        }
    }

    if(vm.count("fullscreen"))
    {
        video_mode = sf::VideoMode::getDesktopMode();
        style = sf::Style::Fullscreen;
        std::cout<<"Running in fullscreen"<<std::endl;
    }
    else
    {
        video_mode = sf::VideoMode(500,500);
    }

    if(vm.count("size"))
    {
        std::string size = vm["size"].as<std::string>();
        std::smatch base_match;
        const std::regex base_regex("([0-9]*)x([0-9]*)");
        if(std::regex_match(size, base_match, base_regex))
        {
            std::string width_string=base_match[1];
            std::string height_string=base_match[2];

            width = std::stoi(width_string);
            height = std::stoi(height_string);

            if(width>video_mode.width||height>video_mode.height)
            {
                std::cerr<<"The size cannot be bigger than screen resolution"<<std::endl;
                return 1;
            }

            std::cout<<"The size set to "<<size<<std::endl;
        }
        else{
            std::cerr<<"The size must be written as widthxheight i.e. 192x108"<<std::endl;
            return 1;
        }
    }

    create_board();
    window.create(video_mode,"Game of life",style);
    init_shapes();
    if(vm.count("draw"))
        draw_board();
    else
        fill_board_with_random_values();
    
    sf::Clock clock;
    show_board();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (
                event.type == sf::Event::KeyPressed 
                && event.key.code == sf::Keyboard::Escape
                || event.type == sf::Event::Closed
            )
                window.close();
        }
        if(clock.getElapsedTime().asMilliseconds()>=250)
        {
            clock.restart();
            for(int y = 0;y<height;y++){
                for(int x = 0;x<width;x++)
                {
                    if(game_board_1[x][y])
                        if(!vector_contains(survive,count_living_neighbours(x,y)))
                            game_board_2[x][y]=false;
                    else
                        if(vector_contains(birth,count_living_neighbours(x,y)))
                            game_board_2[x][y]=true;

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
