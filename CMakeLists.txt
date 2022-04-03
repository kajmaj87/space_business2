cmake_minimum_required(VERSION 3.18)

# create project
project(spacebusiness 
    VERSION 0.1 
    DESCRIPTION "An economy simulation of space proportions"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(NOT EMSCRIPTEN) # do not perform those checks when building for webasm
 set(CMAKE_CXX_CLANG_TIDY clang-tidy)
 set(CMAKE_CXX_CPPCHECK "cppcheck")
else()
    #string(APPEND CMAKE_CXX_FLAGS " -s ASSERTIONS=1") 
    string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 
endif()

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

if (EMSCRIPTEN) 
    add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ../docs/generated)
    add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.js ../docs/generated/${PROJECT_NAME}.js)
    add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.wasm ../docs/generated/${PROJECT_NAME}.wasm)
    add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_NAME}.worker.js ../docs/generated/${PROJECT_NAME}.worker.js)
 endif() 