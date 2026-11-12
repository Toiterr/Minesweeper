#include <cstdlib>
#include <Game.h>
#include <Solver.h>
#include <iostream>
#include <iomanip>
#include <cmath>

void show(Game game) { //console visualisation
	std::cout << "====================" << std::endl;
	for (size_t i = 0; i < game.getSize(); i++) {
		for (size_t j = 0; j < game.getSize(); j++) {
			if (game.isOpened(j, i)) { //if not opened - cell shows as #
				if (game.isMine(j, i)) {
					std::cout << "*"; //if you meet a mine - it shows as *
				} else {
					std::cout << game.getAroundMines(j, i); //if you sucessfully opened cell - it shows amount of mines around
				}
			} else {
				if (game.isFlagged(j, i)) {
					std::cout << "?"; //if you flag a cell - it shows as ?
				}
				else {
					std::cout << "#";
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << "====================";
	std::cout << std::endl;
}

int main() {
	std::cout << "Enter size: ";
	size_t n;
	std::cin >> n;
	std::cout << "Choose difficulty(from 1(very easy) to 5(very hard): ";
	size_t diff;
	std::cin >> diff;
	Game a(n, n*n*(std::log(diff+1)/(6.4*std::log(4)))); //n*n/6.4 - a normal difficult's amount of mines in minesweeper games, as i understood it
	while (true) {
		std::cout << "Enter pos to start: ";
		size_t x;
		size_t y;
		std::cin >> x >> y;
		a.start(x - 1, y - 1); //For user friendly interface(for user, counting starts from 1)
		a.open(x - 1, y - 1); //likewise
		show(a);
		bool gameContinues = true;
		Solver solver(a);
		do {	
			std::cout << "Enter operation(0 - open, 1 - flag, 2 - solverStep) and pos: ";
			size_t op;
			size_t x;
			size_t y;
			Result res;
			std::cin >> op;
			switch (op) {
			case 2:
				res = solver.solve(100);
				break;
			case 1:
				std::cin >> x >> y;
				res = a.flag(x - 1, y - 1);
				break;
			default:
				std::cin >> x >> y;
				res = a.open(x - 1, y - 1);
				break;
			}
			switch (res) {
			case Result::InvalidCord:
				std::cout << "You entered invalid coordinates";
				break;
			case Result::AlreadyOpened:
				std::cout << "You already opened that cell";
				break;
			case Result::Win:
				std::cout << "You win!";
				gameContinues = false;
				break;
			case Result::Lose:
				std::cout << "You lose :(";
				gameContinues = false;
				break;
			default:
				break;
			}
			std::cout << std::endl;
			show(a);
			std::cout << std::endl;
		} while (gameContinues);
	}
	return 0;
}