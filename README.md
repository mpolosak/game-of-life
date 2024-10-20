# game-of-life
Conway's Game of Life in C++.  
Compiling and running on Windows and Linux (probably other Unix-like systems too)  
Allows:
* setting custom rules
* drawing a board using a mouse
* saving a board to a text file or an image (PNG, BMP, TGA)
* loading a board from a text file or an image (PNG, BMP, TGA)
* changing colors of the game  
* setting a background of the game
## Dependencies
* [sfml](https://www.sfml-dev.org/)
* [boost](https://www.boost.org/)
## Building on Linux
### Required software
* [cmake](https://cmake.org/)
* [make](https://www.gnu.org/software/make/)
* C++ compiler ([gcc](https://gcc.gnu.org/) or clang)
### Building and installation
```
cmake -B build
make -C build
sudo make -C build install
```
### Building AppImage
```
cmake -B build
make -C build AppImage
```
## Building on Windows
### Required software
* [cmake](https://cmake.org/)
* [mingw-w64](https://www.mingw-w64.org/)
### Building
```
cmake . -G "MinGW Makefiles"
mingw32-make
```
## Running
Run by typing *game-of-life* into terminal.  
Type in *game-of-life -h* to see allowed options.  
Press tab if you want to stop simulation and draw blocks of board using mouse.   
Press Enter or Tab to start end drawing and start simulation.  
End simulation by pressing Escape.