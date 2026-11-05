# Minesweeper library
Welcome to Minesweeper repository. This is my simple library for
minesweeper games.

> [!WARNING]
> That project is currently in development, after pushing it here I'll add:
> - [x] A difficulty settings
> - [ ] A solver algorithm
> - [ ] A strategies's comparasion

## Main Information
Library is single-class and the main code is in two files:


**Game.h:**
```cpp
enum class Result {//All result types};
class Game
{
private:
	struct Cell {...};
	std::vector<Cell> cells_;
	const int gridSize_;
	int count_;
public:
	explicit Game(int n, int mineCount) : ... {}
	Result start(...);
	Result open(...);
	Result flag(...);

	int getAroundMines(...) const;
	...
	//Control methods
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
	//Placing/Removing flag
}
int Game::getAroundMines(...) { ... }
...
//All other methods
```

The repository also have:

1. A probe console-based app to play minesweeper on a NxN field: [main.cpp](./app/main.cpp)  
*With your leave, I'll omit it description [for now](#app).*
2. A tests built using GoogleTest framework: [tests.cpp](./tests/tests.cpp)  
*Omit that [too](#tests).*

## Main Point and usage

### Field and cells

Library implements simple concept:

* You can create a NxN matrix of cells - structures, that can be flagged, opened or contain a mine:
```cpp
struct Cell {
	int aroundmines = 0;
	bool opened = false;
	bool mine = false;
	bool flagged = false;
};
```

* To begin, create a **Game** object and initialize the match:

```cpp
Game game(5, 10); //arguments is grid size (NxN) and count of mines
a.start(3, 4) //arguments is starting position(always safe)
```

* The library also provides methods to interact with certain cells using their coordinates (getAroundMines for example):

```cpp
int Game::getAroundMines(int x, int y) const {
	if (x &lt; 0 || x &gt;= gridSize_ || y &lt; 0 || y &gt;= gridSize_) {
		return 0;
	}
	return cells_[y*gridSize_+x].aroundmines;
}
```
---
Once you include the library, you can, *for example*, check whether a specific cell at (x,y) has a flag:
```cpp
if (game.isFlagged(x, y)) {
	return "You already flagged that cell";
}
```

### In-game interaction

The library have an result enumerate to track game process:
```cpp
enum class Result {
	Sucess,
	Lose,
	Win,
	InvalidCord,
	AlreadyOpened
};
```

Along with the interaction methods themselfs:
```cpp
Result start(int x, int y);
Result open(int x, int y);
Result flag(int x, int y);
```

Each interaction returns some "result" that can be checked:
```cpp
if (a.open(x, y) == Result::Lose) {
	return "You lose";
}
```
---
All that gives you full control over game execution. You can
* Build your own UI:
```cpp
if (//User Clicks Button) {
	game.open(x, y);
	...
}
```
* Define your own rules:
```cpp
if (game.open(x, y) == Result::Lose) {
	player.hp -= 1;
	//Continue the game
}
```
* *And some other stuff that i can't imagine*

# App
This project also have a [console-based app](/app/main.cpp) showcasing the library's capabilities

The `.cpp` file is thoroughly commented, *so I see no point in describing it here in detail.*

# Tests
I have integrated the GoogleTest framework and tested in [separated file](/tests/tests.cpp) 5 aspects/rules:

1. The starting cell(*which coordinates you put in game.start(..)*) is always safe
2. The mine count which you put in game constructor mathes the real count of mines on field
3. You can't open any cell by using game.flag(...)
4. The win condition triggers properly when all mines are flagged.
5. The lose condition triggers properly upon opening a mine.

> [!NOTE]
> I can add more tests at the future

All tests are passed, you can prove it by yourself by launching [tests file](/tests/tests.cpp)
