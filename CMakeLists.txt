cmake_minimum_required(VERSION 3.13)
project(game-of-life)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

if (MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.1
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML)

set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
include(FetchContent)
FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.86.0
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(Boost)

add_executable(game-of-life src/main.cpp src/gameoflife.cpp src/board.cpp src/config.cpp src/boardconfig.cpp
    src/utilities.cpp src/appearanceconfig.cpp src/background.cpp)

target_link_libraries(game-of-life sfml-graphics sfml-system sfml-window Boost::program_options)

install(TARGETS game-of-life)
IF (UNIX AND NOT APPLE)
    install(FILES "game-of-life.desktop" DESTINATION "share/applications")
    install(DIRECTORY "icons/" DESTINATION "share/icons/hicolor")
ENDIF()
IF (LINUX)
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/Appdir/ 
        DEPENDS game-of-life
        DEPENDS icons/
        COMMAND ${CMAKE_COMMAND} --install ${PROJECT_BINARY_DIR} --prefix ${PROJECT_BINARY_DIR}/AppDir/usr
    )
    set(linuxdeploy ${PROJECT_BINARY_DIR}/linuxdeploy-x86_64.AppImage)
    file(
        GENERATE OUTPUT ${PROJECT_BINARY_DIR}/linuxdeploy.cmake
        CONTENT "file(DOWNLOAD\
        https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage ${linuxdeploy})\n\
        file(CHMOD ${linuxdeploy} PERMISSIONS OWNER_EXECUTE OWNER_READ)"
    )
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/linuxdeploy-x86_64.AppImage
        COMMAND ${CMAKE_COMMAND} -P ${PROJECT_BINARY_DIR}/linuxdeploy.cmake
    )
    add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/Game_of_life-x86_64.AppImage
        DEPENDS ${PROJECT_BINARY_DIR}/Appdir/ 
        DEPENDS ${PROJECT_BINARY_DIR}/linuxdeploy-x86_64.AppImage
        COMMAND ${PROJECT_BINARY_DIR}/linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
    )
    add_custom_target(AppImage DEPENDS ${PROJECT_BINARY_DIR}/Game_of_life-x86_64.AppImage) 
ENDIF()