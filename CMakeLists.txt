cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)

set(FB_TARGET bs_pre)

project(game1)


find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp Source/Animation.cpp Source/Entity.cpp Source/Game.cpp
                               Source/Level.cpp Source/parser.cpp Source/Player.cpp Source/tinyxml2.cpp Source/menu.cpp Headers/menu.h)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Images $<TARGET_FILE_DIR:${PROJECT_NAME}>/Images)
