#pragma once
#include <algorithm>
#include <random>
#include <vector>

//allows to do any operation with any parameter and just check what will happen
enum class Result {
	Sucess,
	Lose,
	Win,
	InvalidCord,
	AlreadyOpened
};

class Game {
private:
	struct Cell {
		int aroundmines = 0; //(4)
		bool opened = false; //(1)
		bool mine = false; //(2)
		bool flagged = false; //(3)
	};
	std::vector<Cell> cells_; //a vector of cells, each of which can be opened(1), have a mine(2) or a flag(3), and stores amount of around mines(4)
	//to user - cells_ is a 2D matrix in cartesian coord., so after input (x,y) -> cells_[y * gridSize_ + x]
	const int gridSize_;
	int count_;
public:
	explicit Game(int n, int mineCount) : gridSize_(n), count_(mineCount) {
		cells_.resize(gridSize_*gridSize_, Cell(0,0,0,0)); //before initialising cells_ is 0 size
	}
	Result start(int x, int y);
	Result open(int x, int y);
	Result flag(int x, int y);

	void setMine(int x, int y, bool state);
	int getAroundMines(int x, int y) const;
	int getSize() const;
	bool isMine(int x, int y) const;
	bool isFlagged(int x, int y) const;
	bool isOpened(int x, int y) const;
};