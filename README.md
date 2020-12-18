# game-of-life
Conway's Game of Life in C++.  
Allows:
* setting custom rules
* drawing a board using a mouse
* saving a board to a file
* loading a board from a file  
## Dependencies
* [sfml](https://www.sfml-dev.org/)
* [boost](https://www.boost.org/)
## Building and installation
```
meson build
ninja -C build
sudo ninja -C build install
```
## Running
Run by typing *game-of-life* into terminal.  
Type in *game-of-life -h* to see allowed options.  
Press tab if you want to stop simulation and draw blocks of board using mouse.   
Press Enter or Tab to start end drawing and start simulation.  
End simulation by pressing Escape.