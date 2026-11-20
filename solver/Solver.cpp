#include "Solver.h"

//std::vector<bool> Solver::systemSolve(std::vector<Constraint> system) {
//
//}

Result Solver::step() {
	static short dirx[8] = { 0, 0, -1, -1, -1, 1, 1, 1 };
	static short diry[8] = { -1, 1, -1, 0, 1, -1, 0, 1 };
	Result res = Result::Sucess;
	std::vector<Constraint> system;
	size_t size = game_.getSize();

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (res < Result::Sucess) {
				return res;
			}
			if (!game_.isOpened(x, y)) {
				continue;
			}

			int flags = 0;
			int closed = 0;

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

					//flags += game_.isFlagged(x + dirx[i], y + diry[i]);
					//closed += !game_.isOpened(x + dirx[i], y + diry[i]);
				}
			}

			if (!c.mines) {
				for (auto i = c.variables.begin(); i != c.variables.end(); ++i) {
					res = game_.open(*i % size, *i / size);
				}
				//for (int i = 0; i < 8; i++) {
				//	if (!game_.isFlagged(x + dirx[i], y + diry[i])) {
				//		res = game_.open(x + dirx[i], y + diry[i]);
				//	}
				//}
			}
			else if (c.mines == c.variables.size()) {
				for (auto i = c.variables.begin(); i != c.variables.end(); ++i) {
					res = game_.flag(*i % size, *i / size);
				}
				//for (int i = 0; i < 8; i++) {
				//	if (!game_.isOpened(x + dirx[i], y + diry[i]) && !game_.isFlagged(x + dirx[i], y + diry[i])) {
				//		res = game_.flag(x + dirx[i], y + diry[i]);
				//	}
				//}
			}
			else {
				system.push_back(c);
			}
		}
	}
	if (system.size() > 0) {
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

		while (!adjList.empty()) {
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
		}
	}
	//for (auto i = systemSolve(subSystem) { if *i - flag / else - open }
	return res;
}

Result Solver::solve(int maxSteps) {
	Result res = step();

	for (size_t i = 0; i < maxSteps; i++) {
		res = step();
		if (res < Result::Sucess) {
			break;
		}
	}
	return res;
}