cmake_minimum_required(VERSION 3.12)


file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" FOLDER_NAME ${FOLDER_NAME})

add_library(${FOLDER_NAME} OBJECT ${SOURCES})
target_link_libraries(${FOLDER_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

#target_include_directories(${FOLDER_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
