#include"gameoflife.h"

int main(int argc, char *argv[])
{
    try{
        GameOfLife game_of_life(argc, argv);   
        game_of_life.run();
    }
    catch(std::string &error)
    {
        std::cerr<<error<<std::endl;
        return 1;
    }
    return 0;
}