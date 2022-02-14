cmake_minimum_required(VERSION 3.13)
project(game_of_life)

IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically
    set(SFML_STATIC_LIBRARIES TRUE)
    
    add_compile_definitions(__STDC_LIB_EXT1__)
    if(MINGW)
        message(STATUS "Use -static-libgcc -static-libstdc++")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    endif()
ENDIF()

# PNG++_DIR is a path do dir with png++ dir
# When not set by argument to cmake its value is set to CMAKE_CURRENT_DIR
# Change it if you have your png++ in other dir
# If you have it in /usr/include you don't need to do anything since cmake
# includes all of /usr/include
message(STATUS "PNG++_DIR set to ${PNG++_DIR}")

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)
include(FindPNG)
find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(game_of_life src/main.cpp src/board.cpp src/config.cpp src/boardconfig.cpp
    src/utilities.cpp src/appearanceconfig.cpp src/background.cpp)

target_link_libraries(game_of_life sfml-graphics sfml-system sfml-window ${PNG_LIBRARIES Boost::program_options)
target_include_directories(game_of_life PUBLIC "${PNG++_DIR}")

include(CPack)
install(TARGETS game_of_life)
install(IMPORTED_RUNTIME_ARTIFACTS game_of_life RUNTIME)
IF (UNIX AND NOT APPLE)
    install(FILES "game-of-life.desktop" DESTINATION "share/applications")
    install(DIRECTORY "icons/" DESTINATION "share/icons/hicolor")
ELSEIF(WIN32)
    install(FILES ${PNG_LIBRARIES} DESTINATION "bin")
ENDIF()