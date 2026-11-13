#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <queue>

//allows to do any operation with any parameter and just check what will happen
enum class Result {
	Lose,
	Win,
	Sucess,
	InvalidCord,
	AlreadyOpened
};

class Game {
private:
	struct Cell {
		size_t aroundmines = 0; //(4)
		bool opened = false; //(1)
		bool mine = false; //(2)
		bool flagged = false; //(3)
	};
	std::vector<Cell> cells_; //a vector of cells, each of which can be opened(1), have a mine(2) or a flag(3), and stores amount of around mines(4)
	//to user - cells_ is a 2D matrix in cartesian coord., so after input (x,y) -> cells_[y * gridSize_ + x]
	const size_t gridSize_;
	const size_t maxCount_;
	size_t count_;
public:
	explicit Game(size_t n, size_t mineCount) : gridSize_(n), maxCount_(mineCount) {
		cells_.resize(gridSize_*gridSize_, Cell(0,0,0,0)); //before initialising cells_ is 0 size
	}
	Result start(size_t x, size_t y);
	Result open(size_t x, size_t y);
	Result flag(size_t x, size_t y);

	void setMine(size_t x, size_t y, bool state);
	size_t getAroundMines(size_t x, size_t y) const;
	size_t getSize() const;
	bool isMine(size_t x, size_t y) const;
	bool isFlagged(size_t x, size_t y) const;
	bool isOpened(size_t x, size_t y) const;
};