cmake_minimum_required(VERSION 3.13)
project(game-of-life)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.1
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML)

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(game-of-life src/main.cpp src/gameoflife.cpp src/board.cpp src/config.cpp src/boardconfig.cpp
    src/utilities.cpp src/appearanceconfig.cpp src/background.cpp)

target_link_libraries(game-of-life sfml-graphics sfml-system sfml-window Boost::program_options)

install(TARGETS game-of-life)
IF (UNIX AND NOT APPLE)
    install(FILES "game-of-life.desktop" DESTINATION "share/applications")
    install(DIRECTORY "icons/" DESTINATION "share/icons/hicolor")
ENDIF()