#include "Solver.h"

Result Solver::step() {
	static int dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	static int diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };
	Result res = Result::Sucess;

	for (int x = 0; x < game.getSize(); x++) {
		for (int y = 0; y < game.getSize(); y++) {
			if (res < Result::Sucess) {
				return res;
			}
			if (!game.isOpened(x, y)) {
				continue;
			}

			int flags = 0;
			int closed = 0;

			for (int i = 0; i < 8; i++) {
				if (x + dirx[i] >= 0 && x + dirx[i] < game.getSize() &&
					y + diry[i] >= 0 && y + diry[i] < game.getSize()) {
					flags += game.isFlagged(x + dirx[i], y + diry[i]);
					closed += !game.isOpened(x + dirx[i], y + diry[i]);
				}
			}

			if (flags == game.getAroundMines(x, y)) {
				for (int i = 0; i < 8; i++) {
					if (!game.isFlagged(x + dirx[i], y + diry[i])) {
						res = game.open(x + dirx[i], y + diry[i]);
					}
				}
			}
			else if (closed == game.getAroundMines(x, y)) {
				for (int i = 0; i < 8; i++) {
					if (!game.isOpened(x + dirx[i], y + diry[i]) && !game.isFlagged(x + dirx[i], y + diry[i])) {
						res = game.flag(x + dirx[i], y + diry[i]);
					}
				}
			}
		}
	}
	return res;
}

Result Solver::solve(int maxSteps) {
	Result res = step();

	for (int i = 0; i < maxSteps; i++) {
		res = step();
		if (res < Result::Sucess) {
			break;
		}
	}
	return res;
}