#include <gtest/gtest.h>
#include <Game.h>
//idk what to describe here +_+

TEST(GameTest, StartCellWithoutMine) {
	for (int n = 1; n < 10; n++) {
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				Game a(n, n * n - 1);
				a.start(x, y);
				EXPECT_FALSE(a.isMine(x, y));
			}
		}
	}
}

TEST(GameTest, CorrectMineAmount) {
	for (int n = 1; n < 10; n++) {
		for (int am = 0; am < n * n; am++) {
			Game a(n, am);
			a.start(0, 0);
			int amount = 0;
			for (int i = 0; i < a.getSize(); i++) {
				for (int j = 0; j < a.getSize(); j++) {
					amount += a.isMine(i, j);
				}
			}
			EXPECT_EQ(amount, am);
		}
	}
}

TEST(GameTest, FlaggingIsntOpening) {
	for (int n = 1; n < 10; n++) {
		Game a(n, n * n / 6.4);
		a.start(0, 0);
		a.open(0, 0);
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				a.flag(x, y);
			}
		}
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				EXPECT_TRUE(a.isFlagged(x, y) != a.isOpened(x, y));
			}
		}
	}
}

TEST(GameTest, WinCondition) {
	for (int n = 2; n < 10; n++) {
		Game a(n, n * n - 1);
		a.start(0, 0);
		Result res;
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (a.isMine(x, y)) {
					res = a.flag(x, y);
				}
			}
		}
		ASSERT_EQ(res, Result::Win);
	}
}

TEST(GameTest, LoseCondition) {
	for (int n = 2; n < 10; n++) {
		Game a(n, n * n - 1);
		a.start(0, 0);
		Result res;
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				if (a.isMine(x, y)) {
					res = a.open(x, y);
					break;
				}
			}
		}
		EXPECT_EQ(res, Result::Lose);
	}
}