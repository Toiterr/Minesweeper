# Minesweeper library
Welcome to the Minesweeper repository. This is my simple library for minesweeper games.

> [!WARNING]
> That project is currently in development, after pushing it here, I plan to add:
> - [x] Difficulty settings
> - [ ] Solver algorithm
> - [ ] Strategy comparison

## Main Information
Library is single-class and all main code is in two files:


**Game.h:**
```cpp
enum class Result {//All result types};
class Game
{
private:
	struct Cell {...};
	std::vector&lt;std::vector&lt;Cell&gt;&gt; cells_;
	const int gridSize_;
	int count_;
public:
	explicit Game(int n, int mineCount) : ... {}
	Result start(...);
	Result open(...);
	Result flag(...);

	int getAroundMines(...) const;
	...
	//Getters
};
```

And **Game.cpp:**
```cpp
Result Game::start(...) {
	//(Re)Initializing and random mine placement
}
Result Game::open(...) {
	//Checking (is_mine?) and DFS opening if it's no mines around
}
Result Game::flag(...) {
	//Placing/Removing flag and checking win condition
}
int Game::getAroundMines(...) { ... }
...
//All other getters
```

The repository also includes:

1. A probe console-based app to play minesweeper on an NxN field: main.cpp  
*With your leave, I'll omit it's description [for now](#app).*
2. Tests, created using GoogleTest  
*Omit that [too](#tests).*

## Main Interface and usage

### Field and cells

Library implements a simple concept:

* You can create an NxN matrix of cells - structures, that can be flagged, opened or contain a mine:
```cpp
struct Cell {
	int aroundmines = 0;
	bool opened = false;
	bool mine = false;
	bool flagged = false;
};
```

* You can create an object of the "Game" type and then start a game:

```cpp
Game game(5, 10); //arguments is grid size (NxN) and count of mines
a.start(3, 4) //arguments is starting position(always safe)
```

* The library also provides methods to interact with certain cells by their position(getAroundMines for example):

```cpp
int Game::getAroundMines(int x, int y) const {
	if (x &lt; 0 || x &gt;= gridSize_ || y &lt; 0 || y &gt;= gridSize_) {
		return 0;
	}
	return cells_[y][x].aroundmines;
}
```
---
So, if you include library, you can, *for example*, check if there is a mine or a flag in position (x,y):
```cpp
if (game.isFlagged(x, y)) {
	return "You already flagged that cell";
}
```

### In-game interaction

The library also includes a result enumerate, which allows you to track the game process:
```cpp
enum class Result {
	Sucess,
	Lose,
	Win,
	InvalidCord,
	AlreadyOpened
};
```

And the interaction methods themselves:
```cpp
Result start(int x, int y);
Result open(int x, int y);
Result flag(int x, int y);
```

As you can see, all interaction return a "result" that can be checked:
```cpp
if (a.open(x, y) == Result::Lose) {
	return "You lose";
}
```
---
All of this allows you to fully control the game. You can
* Set your own UI:
```cpp
if (//User Clicks Button) {
	game.open(x, y);
	...
}
```
* Set your own rules:
```cpp
if (game.open(x, y) == Result::Lose) {
	player.hp -= 1;
	//Continue the game
}
```
* *And some other stuff that i can't imagine*

# App
This project also includes a [console-based app](/app/main.cpp) that demonstrates the capabilities of the library.

The [".cpp"](/src/Game.cpp) file contains all the necessary comments for understaning. *I see no point in describing it here in detail.*

# Tests
I have integrated the GoogleTest framework and tested in [separated file](/tests/tests.cpp) 5 aspects/rules:

1. The starting cell(*which coordinates you put in game.start(..)*) is always safe
2. Mine count which you put in game constructor matches the real count of mines on field
3. Is an amount of mines around an opened cell countering correctly
4. When you use game.flag(..) you can't open any cell
5. Is a win condition(all mines have flags) works correctly
6. Is a lose condition(opening a mine) works correctly

> [!NOTE]
> I may add more tests in the future

All tests pass, you can verify it yourself by launching [tests file](/tests/tests.cpp)
