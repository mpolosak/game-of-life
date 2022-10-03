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
* [meson](https://mesonbuild.com/)
* [ninja](https://ninja-build.org/)
* C++ compiler ([gcc](https://gcc.gnu.org/) or clang)
### Building and installation
```
meson build
ninja -C build
sudo ninja -C build install
```
### Building AppImage
```
meson build -Dprefix=AppDir
ninja -C build install
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir
./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage

```
## Building on Windows
### Required software
* [cmake](https://cmake.org/)
* [mingw-w64](https://www.mingw-w64.org/)
### Building
```
cmake . -G "MinGW Makefiles" -D "BOOST_ROOT=boost_root" -D "BOOST_LIBRARYDIR=boost_librarydir" -D "BOOST_INCLUDEDIR=boost_includedir"
mingw32-make
```
## Running
Run by typing *game-of-life* into terminal.  
Type in *game-of-life -h* to see allowed options.  
Press tab if you want to stop simulation and draw blocks of board using mouse.   
Press Enter or Tab to start end drawing and start simulation.  
End simulation by pressing Escape.