# CMakeLists.txt
cmake_minimum_required(VERSION 3.22)   

# Declare our project
project("Connect4") 

find_package(Catch2 REQUIRED)

include_directories(include)

set(SOURCES src/main.cpp src/Game.cpp src/Board.cpp src/BoardPosition.cpp src/BotPlayer.cpp src/HumanPlayer.cpp src/Player.cpp)

# Add our main executable

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

# set C++ version for both targets
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

option(BUILD_TESTING "Builds only the test executable." OFF)
option(CODE_COVERAGE "Collect coverage from test library" OFF)

target_link_libraries(${PROJECT_NAME} Catch2::Catch2WithMain)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
