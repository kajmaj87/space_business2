cmake_minimum_required(VERSION 3.18)
# create project
project(spacebusiness 
    VERSION 0.1.2
    DESCRIPTION "An economy simulation of space proportions"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(NOT EMSCRIPTEN) # do not perform those checks when building for webasm
#  set(CMAKE_CXX_CLANG_TIDY clang-tidy)
#  set(CMAKE_CXX_CPPCHECK "cppcheck")
else()
    #string(APPEND CMAKE_CXX_FLAGS " -s ASSERTIONS=1") 
    string(APPEND CMAKE_CXX_FLAGS " -s USE_PTHREADS") 
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ASYNCIFY") 
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s PROXY_TO_PTHREAD") 
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -s ALLOW_MEMORY_GROWTH=1") 
endif()

# add executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-literal-suffix -Wno-reserved-user-defined-literal -Wno-user-defined-literals)
target_include_directories(${PROJECT_NAME} PRIVATE src)


# add dependencies
include(cmake/CPM.cmake)
CPMAddPackage("gh:ArthurSonzogni/FTXUI@2.0.0")
CPMAddPackage("gh:skypjack/entt@3.9.0")
CPMAddPackage("gh:fmtlib/fmt#8.1.1")
CPMAddPackage("gh:gabime/spdlog@1.10.0")

# link dependencies
target_link_libraries(${PROJECT_NAME} 
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
    PRIVATE EnTT
    PRIVATE fmt
    PRIVATE spdlog::spdlog)

add_subdirectory(src/ui)
add_subdirectory(src/core)

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
