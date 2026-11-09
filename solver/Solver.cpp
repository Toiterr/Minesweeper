#include "Solver.h"

void Solver::step() {
	int dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	int diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };

	for (int x = 0; x < game.getSize(); x++) {
		for (int y = 0; y < game.getSize(); y++) {
			if (game.isOpened(x, y)) {
				int flags = 0;
				int opened = 0;
				for (int i = 0; i < 8; i++) {
					if (x + dirx[i] >= 0 && x + dirx[i] < game.getSize() &&
						y + diry[i] >= 0 && y + diry[i] < game.getSize()) {
						flags += game.isFlagged(x + dirx[i], y + diry[i]);
						opened += game.isOpened(x + dirx[i], y + diry[i]);
					}
				}
				if (flags == game.getAroundMines(x, y)) {
					for (int i = 0; i < 8; i++) {
						if (!game.isFlagged(x + dirx[i], y + diry[i])) {
							game.open(x + dirx[i], y + diry[i]);
						}
					}
				}
				else if (8 - opened == game.getAroundMines(x, y)) {
					for (int i = 0; i < 8; i++) {
						if (!game.isOpened(x + dirx[i], y + diry[i]) && !game.isFlagged(x + dirx[i], y + diry[i])) {
							game.flag(x + dirx[i], y + diry[i]);
						}
					}
				}
			}
		}
	}
}