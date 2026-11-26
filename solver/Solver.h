#include "Game.h"
#include <unordered_set>
#include <unordered_map>

struct Constraint {
	std::vector<int> variables;
	int mines;
};

class Solver {
private:
	Game& game_;
	size_t size;
	std::unordered_map<int, int> solutions;
	static constexpr int dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	static constexpr int diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };
public:
	Solver(Game& g) : game_(g), size(g.getSize()) {};
	std::unordered_map<int, int> systemSolve(std::vector<Constraint> sys);
	Result step();
	Result system();
	Result probabilities(int maxSteps);
	Result solve(int maxSteps);
};

