#include "Game.h"

class Solver {
private:
	Game& game;
public:
	Solver(Game& g) : game(g) {};
	Result step();
	Result solve(int maxSteps);
};