cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_ROOT}/Modules/"  "/usr/share/SFML/cmake/Modules/")

project(SnakeGame)

add_subdirectory(State)
add_subdirectory(ResourceManager)
add_subdirectory(Game)
add_subdirectory(MainMenu)
add_subdirectory(GamePlay)
add_subdirectory(Snake)

set(SOURCE main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
                                      State
                                      Snake
                                      MainMenu
                                      Game
                                      GamePlay
                                      ResourceManager)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-audio sfml-window)
