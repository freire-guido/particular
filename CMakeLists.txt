cmake_minimum_required(VERSION 3.8)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(SFML_LIBS sfml-system sfml-window sfml-graphics)
file(GLOB SOURCES src/*.cpp)

add_executable(particular ${WIN32_GUI} ${SOURCES})
target_include_directories(particular PRIVATE "include" "lib")
target_link_libraries(particular ${SFML_LIBS})