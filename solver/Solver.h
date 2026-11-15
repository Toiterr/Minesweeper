#include "Game.h"

struct Constraint {
	std::vector<int> variables;
	int mines;
};

class Solver {
private:
	Game& game_;
public:
	Solver(Game& g) : game_(g) {};
	Result step();
	Result solve(int maxSteps);
	//std::vector<bool> systemSolve(std::vector<Constraint> system);
};

