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

find_package(SFML 2.5.1 COMPONENTS graphics system window REQUIRED)
find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(game_of_life src/main.cpp src/board.cpp src/config.cpp src/boardconfig.cpp
    src/utilities.cpp src/appearanceconfig.cpp src/background.cpp)

target_link_libraries(game_of_life sfml-graphics sfml-system sfml-window Boost::program_options)

include(CPack)
install(TARGETS game_of_life)
install(IMPORTED_RUNTIME_ARTIFACTS game_of_life RUNTIME)
IF (UNIX AND NOT APPLE)
    install(FILES "game-of-life.desktop" DESTINATION "share/applications")
    install(DIRECTORY "icons/" DESTINATION "share/icons/hicolor")
ENDIF()