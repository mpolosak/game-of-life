# game-of-life
Conway's Game of Life in C++.  
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
## Building and installation
```
meson build
ninja -C build
sudo ninja -C build install
```
## Building AppImage
```
meson build -Dprefix=AppDir
ninja -C build install
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir
./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage

```
## Running
Run by typing *game-of-life* into terminal.  
Type in *game-of-life -h* to see allowed options.  
Press tab if you want to stop simulation and draw blocks of board using mouse.   
Press Enter or Tab to start end drawing and start simulation.  
End simulation by pressing Escape.