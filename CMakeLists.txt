

cmake_minimum_required(VERSION 3.20)

project(Minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(CMAKE_TLS_VERIFY OFF)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_library(Minesweeper STATIC
	src/Game.cpp
)

target_include_directories(Minesweeper
	PUBLIC
		minesweeper
)

add_executable(MinesweeperTests
	tests/tests.cpp
)

target_link_libraries(MinesweeperTests
	PRIVATE
		Minesweeper
		gtest gtest_main
)

add_library(MinesweeperAlg
	solver/Solver.cpp
)

target_include_directories(MinesweeperAlg
	PUBLIC
		solver
)

target_link_libraries(MinesweeperAlg
	PRIVATE
		Minesweeper
)

add_executable(MinesweeperApp
	app/main.cpp
)

target_link_libraries(MinesweeperApp
	PRIVATE
		Minesweeper
		MinesweeperAlg
)