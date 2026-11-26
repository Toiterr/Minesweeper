#include "Solver.h"
#include <iostream>

Result Solver::step() {
	Result res = Result::Success;

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (!game_.isOpened(x, y)) {
				continue;
			}

			int around = game_.getAroundMines(x, y);
			int closed = 0;

			for (int i = 0; i < 8; i++) {
				if (x + dirx[i] >= 0 && x + dirx[i] < size &&
					y + diry[i] >= 0 && y + diry[i] < size) {
					around -= game_.isFlagged(x + dirx[i], y + diry[i]);
					closed += !(game_.isOpened(x + dirx[i], y + diry[i]) || game_.isFlagged(x+dirx[i], y+diry[i]));
				}
			}

			if (around == 0 || closed == around) {
				bool t = around;
				for (int i = 0; i < 8; i++) {
					if (x + dirx[i] >= 0 && x + dirx[i] < size &&
						y + diry[i] >= 0 && y + diry[i] < size &&
						!(game_.isOpened(x + dirx[i], y + diry[i]) || game_.isFlagged(x + dirx[i], y + diry[i]))) {
						if (t) {
							res = game_.flag(x + dirx[i], y + diry[i]);
						}
						else {
							res = game_.open(x + dirx[i], y + diry[i]);
						}
					}
				}

			} else {
				res = Result::AlreadyOpened;
			}
		}
	}
	if (res == Result::Win) {
		return res;
	}
	return Result::Success;
}

//std::unordered_map<int, int> Solver::systemSolve(std::vector<Constraint> sys) {
//};

Result Solver::system() {
	Result res = Result::AlreadyOpened;
	std::vector<Constraint> system;

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (!game_.isOpened(x, y)) {
				continue;
			}
			Constraint c;
			c.mines = game_.getAroundMines(x, y);
			for (int i = 0; i < 8; i++) {
				if (x + dirx[i] >= 0 && x + dirx[i] < size &&
					y + diry[i] >= 0 && y + diry[i] < size) {
					if (game_.isFlagged(x + dirx[i], y + diry[i])) {
						c.mines--;
					}
					else if (!game_.isOpened(x + dirx[i], y + diry[i])) {
						c.variables.push_back((y + diry[i]) * size + x + dirx[i]);
					}
				}
			}
			if (!c.mines || c.mines == c.variables.size()) {
				return Result::Success; //Guard clause
			}
			system.push_back(c);
		}
	}

	if (!system.size()) {
		return Result::Success;
	}

	std::unordered_map<int, std::unordered_set<int>> adjList;
	for (auto constr : system) {
		for (auto var1 : constr.variables) {
			for (auto var2 : constr.variables) {
				if (var1 != var2) {
					adjList[var1].insert(var2);
				}
			}
		}
	}

	while (!adjList.empty() || res != Result::Success) {
		std::unordered_set<int> visited;
		std::vector<int> queue;

		int start = adjList.begin()->first;
		visited.insert(start);
		queue.push_back(start);

		for (size_t i = 0; i < queue.size(); ++i) {
			auto it = adjList.find(queue[i]);
			if (it != adjList.end()) {
				for (auto connect : it->second) {
					if (visited.insert(connect).second) {
						queue.push_back(connect);
					}
				}
				adjList.erase(it);
			}
		}

		std::vector<Constraint> subSystem;
		for (auto constr : system) {
			if (visited.contains(constr.variables[0])) {
				subSystem.push_back(constr);
			}
		}

		//std::unordered_map<int, int> probs = systemSolve(subSystem);
		//for (auto& [cell, prob] : probs) {
		//	if (prob == 100) {
		//		res = game_.flag(cell % size, cell / size);
		//	} else if (prob == 0) {
		//		res = game_.open(cell % size, cell / size);
		//	} else {
		//		solutions[cell] = prob;
		//	}
		//}
	}
	return res;
};

Result Solver::probabilities(int maxSteps) {
	//for (auto& [cell, prob] : solutions) {
	//	if (game_.isOpened(cell % size, cell / size)) {
	//		solutions.erase(cell);
	//	}
	//}
	//while (maxSteps > 0) {
	//	maxSteps--;

	//}
	return Result::Success;
};

Result Solver::solve(int maxSteps) {
	Result res = step();
	while (maxSteps > 0) {
		maxSteps--;
		if (res == Result::Win) {
			break;
		}
		if (res == Result::Success) {
			res = step();
		}
		else {
			res = system();
			if (res != Result::Success) {
				res = probabilities(maxSteps / 10);
			}
		}
	}
	return res;
}