#include "Game.h"

//User finalises the field by setting a starting point, which won't have a mine
Result Game::start(size_t x, size_t y) {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return Result::InvalidCord;
	}

	//creating a vector with cells(without starting cell), like a deck of cards
	std::vector<size_t> indexs; 
	for (size_t i = 0; i < gridSize_ * gridSize_; i++) {
		cells_[i] = Cell(0, 0, 0, 0); //erasing previous field, just in parallel
		if (i % gridSize_ != x || i / gridSize_ != y) {
			indexs.push_back(i);
		}
	}

	//reshuffling that "deck"
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(indexs.begin(), indexs.end(), generator);
	
	//picking first count_ cards and saying all of them have mines
	for (auto i = indexs.begin(); i != indexs.begin() + maxCount_; ++i) {
		cells_[*i].mine = true;		
	}

	count_ = maxCount_;
	return Result::Sucess;
}

//opening a cell
Result Game::open(size_t x, size_t y) {
	if (x >= gridSize_ || y >= gridSize_) {
		return Result::InvalidCord;
	}
	if (cells_[y*gridSize_+x].opened) {
		return Result::AlreadyOpened;
	}
	cells_[y*gridSize_+x].opened = true;
	if (cells_[y*gridSize_+x].mine) {
		return Result::Lose;
	}
	//directories to check(neighboring cells)
	static short dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	static short diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };

	size_t aroundmines = 0;
	for (unsigned short i = 0; i < 8; i++) {
		if ((x + dirx[i]) >= 0 && (x + dirx[i]) < gridSize_ && 
			(y + diry[i]) >= 0 && (y + diry[i]) < gridSize_) {
			if (cells_[(y + diry[i]) * gridSize_ + (x + dirx[i])].mine) {
				aroundmines++;
			}
		}
	}
	cells_[y*gridSize_+x].aroundmines = aroundmines;
	if (!count_) {
		return Result::Win;
	}
	if (!aroundmines) { //DFS opening if there is 0 mines around ---- CAUSING STACK OVERFLOW (rewrite to BFS)
		for (unsigned short i = 0; i < 8; i++) {
			if ((x + dirx[i]) >= 0 && (x + dirx[i]) < gridSize_ &&
				(y + diry[i]) >= 0 && (y + diry[i]) < gridSize_) {
				open(x + dirx[i], y + diry[i]);
			}
		}
	}
	return Result::Sucess;
}
//flagging/unflagging a cell
Result Game::flag(size_t x, size_t y) {
	if (x >= gridSize_ || y >= gridSize_) {
		return Result::InvalidCord;
	}
	if (cells_[y*gridSize_+x].opened) {
		return Result::AlreadyOpened;
	}
	if (cells_[y*gridSize_+x].mine) {
		if (cells_[y*gridSize_+x].flagged) {
			count_++; //unflagging
		}
		else {
			count_--; //flagging
		}
	}
	cells_[y*gridSize_+x].flagged = !cells_[y*gridSize_+x].flagged;
	if (!count_) { //win condition - all mines have flags
		return Result::Win;
	}
	return Result::Sucess;
}

void Game::setMine(size_t x, size_t y, bool state) {
	if (x < gridSize_ && y < gridSize_) {
		cells_[y*gridSize_+x].mine = state;
	}
}

//methods to control a game process
size_t Game::getAroundMines(size_t x, size_t y) const {
	if (x >= gridSize_ || y >= gridSize_) {
		return 0;
	}
	return cells_[y*gridSize_+x].aroundmines;
}
size_t Game::getSize() const {
	return gridSize_;
}
bool Game::isFlagged(size_t x, size_t y) const {
	if (x >= gridSize_ || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].flagged;
}
bool Game::isMine(size_t x, size_t y) const {
	if (x >= gridSize_ || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].mine;
}
bool Game::isOpened(size_t x, size_t y) const {
	if (x >= gridSize_ || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].opened;
}