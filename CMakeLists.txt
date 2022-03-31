cmake_minimum_required(VERSION 3.22.3)

# create project
project(spacebusiness 
    VERSION 0.1 
    DESCRIPTION "An economy simulation of space proportions"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_CXX_CPPCHECK "cppcheck")

# add executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# add dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:ArthurSonzogni/FTXUI@2.0.0")
CPMAddPackage("gh:skypjack/entt@3.9.0")

# link dependencies
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
     EnTT)