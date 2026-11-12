#include <algorithm>
#include <gtest/gtest.h>
#include <Game.h>

//idk what to describe here +_+

//TEST(GameTest, MemoryCheck) {
//	for (unsigned int n = 1000; n < 4294967295; n++) {
//		Game a(n, 1);
//		EXPECT_EQ(a.start(n - 1, n - 1), Result::Sucess);
//		EXPECT_EQ(a.open(n - 1, n - 1), Result::AlreadyOpened);
//		EXPECT_EQ(a.flag(0, 0), Result::Sucess);
//		EXPECT_EQ(a.flag(n - 1, 0), Result::Sucess);
//		EXPECT_EQ(a.flag(0, n - 1), Result::Sucess);
//	}
//}
//!!! - STACK OVERFLOW BECAUSE OF DFS OPENING

TEST(GameTest, StartCellWithoutMine) {
	for (unsigned int n = 1; n < 10; n++) {
		for (size_t x = 0; x < n; x++) {
			for (size_t y = 0; y < n; y++) {
				Game a(n, n * n - 1);
				a.start(x, y);
				EXPECT_FALSE(a.isMine(x, y));
			}
		}
	}
}

TEST(GameTest, CorrectMineAmount) {
	for (unsigned int n = 1; n < 10; n++) {
		for (size_t am = 0; am < n * n; am++) {
			Game a(n, am);
			a.start(0, 0);
			size_t amount = 0;
			for (size_t i = 0; i < a.getSize(); i++) {
				for (size_t j = 0; j < a.getSize(); j++) {
					amount += a.isMine(i, j);
				}
			}
			EXPECT_EQ(amount, am);
		}
	}
}

TEST(GameTest, CorrectAroundMinesCount) {
	for (unsigned int n = 1; n < 10; n++) {
		for (size_t am = 0; am < n * n; am++) {
			Game a(n, am);
			a.start(0, 0);
			for (size_t x = 0; x < a.getSize(); x++) {
				for (size_t y = 0; y < a.getSize(); y++) {
					if (!a.isMine(x, y)) {
						a.open(x, y);
						size_t real = 0;
						for (short dx = -1; dx < 2; dx++) {
							for (short dy = -1; dy < 2; dy++) {
								real += a.isMine(x + dx, y + dy);
							}
						}
						ASSERT_EQ(real, a.getAroundMines(x, y));
					}
				}
			}
		}
	}
}

TEST(GameTest, FlaggingIsntOpening) {
	for (unsigned int n = 1; n < 10; n++) {
		Game a(n, n * n / 6.4);
		a.start(0, 0);
		a.open(0, 0);
		for (size_t x = 0; x < n; x++) {
			for (size_t y = 0; y < n; y++) {
				a.flag(x, y);
			}
		}
		for (size_t x = 0; x < n; x++) {
			for (size_t y = 0; y < n; y++) {
				EXPECT_TRUE(a.isFlagged(x, y) != a.isOpened(x, y));
			}
		}
	}
}

TEST(GameTest, WinCondition) {
	for (unsigned int n = 2; n < 10; n++) {
		Game a(n, n * n - 1);
		a.start(0, 0);
		Result res;
		for (size_t x = 0; x < n; x++) {
			for (size_t y = 0; y < n; y++) {
				if (a.isMine(x, y)) {
					res = a.flag(x, y);
				}
			}
		}
		ASSERT_EQ(res, Result::Win);
	}
}

TEST(GameTest, LoseCondition) {
	for (size_t n = 2; n < 10; n++) {
		Game a(n, n * n - 1);
		a.start(0, 0);
		Result res;
		for (size_t x = 0; x < n; x++) {
			for (size_t y = 0; y < n; y++) {
				if (a.isMine(x, y)) {
					res = a.open(x, y);
					break;
				}
			}
		}
		EXPECT_EQ(res, Result::Lose);
	}
}

TEST(GameTest, Restart) {
	for (size_t n = 4; n <= 10; n++) {
		std::vector<size_t> cellPos;
		size_t diff = n * n / 6.4;
		Game a(n, diff);
		a.start(0, 0);
		a.open(0, 0);
		for (size_t x = 0; x < a.getSize(); x++) {
			for (size_t y = 0; y < a.getSize(); y++) {
				if (a.isMine(x, y)) {
					a.flag(x, y);
					cellPos.push_back(y * a.getSize() + x);
				}
			}
		}
		a.start(0, 0);
		bool randomised = false;
		size_t realCount = 0;
		for (size_t x = 0; x < a.getSize(); x++) {
			for (size_t y = 0; y < a.getSize(); y++) {
				if (a.isMine(x, y)) {
					realCount++;
					if (std::find(cellPos.begin(), cellPos.end(), y * a.getSize() + x) == cellPos.end()) {
						randomised = true;
					}
				}
			}
		}
		EXPECT_EQ(realCount, diff);
		EXPECT_TRUE(randomised);
	
	}
}