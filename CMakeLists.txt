cmake_minimum_required(VERSION 3.12)

project(SnakeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 2.5 or 2.6 (SFML 3 changed its API). On Windows, pass -DSFML_DIR=<path to SFML>/lib/cmake/SFML.
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_subdirectory(State)
add_subdirectory(ResourceManager)
add_subdirectory(Game)
add_subdirectory(Common)
add_subdirectory(Snake)
add_subdirectory(MainMenu)
add_subdirectory(PauseMenu)
add_subdirectory(GamePlay)
add_subdirectory(GameOver)

set(SOURCE main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE
                                      Common
                                      State
                                      Snake
                                      MainMenu
                                      PauseMenu
                                      Game
                                      GamePlay
                                      GameOver
                                      ResourceManager
                                      sfml-graphics
                                      sfml-window
                                      sfml-system)

# The game loads assets/... relative to the folder it runs in: copy them next to the executable.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Windows: copy the SFML DLLs next to the executable so it starts with a double-click.
if(WIN32 AND NOT SFML_STATIC_LIBRARIES AND NOT CMAKE_VERSION VERSION_LESS 3.21)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS)
endif()
