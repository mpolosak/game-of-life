cmake_minimum_required(VERSION 3.13)
project(game_of_life)

IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)
include(FindPNG)
find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(game_of_life src/main.cpp src/board.cpp src/config.cpp src/boardconfig.cpp
    src/utilities.cpp src/appearanceconfig.cpp src/background.cpp)

target_link_libraries(game_of_life sfml-graphics sfml-system sfml-window PNG::PNG Boost::program_options)