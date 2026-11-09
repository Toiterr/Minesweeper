#include "Game.h"

//User finalises the field by setting a starting point, which won't have a mine
Result Game::start(int x, int y) {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return Result::InvalidCord;
	}

	//creating a vector with cells(without starting cell), like a deck of cards
	std::vector<int> indexs; 
	for (int i = 0; i < gridSize_ * gridSize_; i++) {
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
	for (auto i = indexs.begin(); i != indexs.begin() + count_; ++i) {
		cells_[*i].mine = true;		
	}
	return Result::Sucess;
}

//opening a cell
Result Game::open(int x, int y) {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
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
	int dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	int diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };

	int aroundmines = 0;
	for (int i = 0; i < 8; i++) {
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
	if (!aroundmines) { //DFS opening if there is 0 mines around
		for (int i = 0; i < 8; i++) {
			if ((x + dirx[i]) >= 0 && (x + dirx[i]) < gridSize_ &&
				(y + diry[i]) >= 0 && (y + diry[i]) < gridSize_) {
				open(x + dirx[i], y + diry[i]);
			}
		}
	}
	return Result::Sucess;
}
//flagging/unflagging a cell
Result Game::flag(int x, int y) {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
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

void Game::setMine(int x, int y, bool state) {
	if (x >= 0 && x < gridSize_ && y >= 0 && y < gridSize_) {
		cells_[y*gridSize_+x].mine = state;
	}
}

//methods to control a game process
int Game::getAroundMines(int x, int y) const {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return 0;
	}
	return cells_[y*gridSize_+x].aroundmines;
}
int Game::getSize() const {
	return gridSize_;
}
bool Game::isFlagged(int x, int y) const {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].flagged;
}
bool Game::isMine(int x, int y) const {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].mine;
}
bool Game::isOpened(int x, int y) const {
	if (x < 0 || x >= gridSize_ || y < 0 || y >= gridSize_) {
		return false;
	}
	return cells_[y*gridSize_+x].opened;
}