# CMakeLists.txt
cmake_minimum_required(VERSION 3.22)   

# Declare our project
project("Connect4")

include_directories(include tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)


set(SOURCES src/Game.cpp src/Board.cpp src/BoardPosition.cpp src/BotPlayer.cpp src/HumanPlayer.cpp src/Player.cpp Test.cc)

# Add our main executable

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

# set C++ version for both targets
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_20)

option(BUILD_TESTING "Builds only the test executable." OFF)
option(CODE_COVERAGE "Collect coverage from test library" OFF)


target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")


enable_testing()

add_executable(
  Test
  Test.cc
  ${SOURCES}
  
)
target_link_libraries(
  Test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Test)


