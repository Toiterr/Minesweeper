#include "Game.h"

class Solver {
private:
	Game& game;
public:
	Solver(Game& g) : game(g) {};
	void step();
};