#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <random>
#include <algorithm>

// # -> wall
// ' ' -> empty space
// $ -> player

typedef enum Difficulty {
	EASY = 1,
	NORMAL,
	HARD,
	CUSTOM
} Difficulty;

bool isAvailable(int width, int height, int nx, int ny, std::vector<std::vector<bool>> visited) {

	if(nx >= 0 && nx < width && ny >= 0 && ny < height) {
		if(visited[nx][ny] == false) {
			return true;
		}
	}

	return false

}


std::vector<std::vector<char>> generateMaze(int width, int height) {

	// maze as 2d vector
	std::vector<std::vector<char>> maze(height, std::vector<char>(width, '#'));

	// stack for randomized dfs
	// holds x,y coordinates
	std::stack<std::pair<int, int>> stack;


	std::vector<std::pair<int, int>> Directions {
		{0, 1}, 	// right
		{0, -1}, 	// left
		{1, 0},	 // down
		{-1, 0} 	// up
	};

	// generating random number
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(Directions.begin(), Directions.end(), gen);


	// starting point
	maze[0][0] = ' ';
	stack.push({0, 0});

	// tracking visited cells
	std::vector<std::vector<bool>> visited {height, std::vector<bool>(width, false)};
	visited[0][0] = true;

	std::pair<int, int> randomDir;


	while(!stack.empty()) {

		// current coordinates
		int cx {stack.top().first};
		int cy {stack.top().second};

		// a random direction selected
		randomDir = Directions[generator(gen)];

		// next coordinates
		int nx {cx + randomDir.first * 2};
		int ny {cy + randomDir.second * 2};


		while(!isAvailable(width, height, nx, ny, visited)) {
			randomDir = Directions[generator(gen)];
			int nx {cx + randomDir.first * 2};
			int ny {cy + randomDir.second * 2};
		}

		// opening the way
		int mx = (cx + nx)/2;
		int my = (cy + ny)/2;
		maze[mx][my] = ' ';
		maze[nx][ny] = ' ';


		stack.push({nx, ny});

	}
	
	return maze;

}

void printMaze(std::vector<std::vector<char>> maze) {

	// clear screen
	std::cout << "\033[H";

	// print top borders
	std::cout << std::string(maze[0].size() + 2, '@');
	std::cout << '\n';
	
	// print maze
	for(int i = 0; i < maze.size(); i++) {

		// print left borders
		std::cout << '@';
		
		for(int j = 0; j < maze[0].size(); j++) {
			std::cout << maze[i][j];
		}

		// print right borders
		std::cout << '@';
		std::cout << '\n';
	}

	// print bottom borders
	std::cout << std::string(maze[0].size() + 2, '@');
	std::cout << '\n';
}

bool isGameWon() {
	return false;
}

int main() {

	Difficulty difficulty;
	int diffSelection;

	std::cout << "Difficulty\n";
	std::cout << "1- 21x21\t 150seconds\n";
	std::cout << "2- 31x31\t 120seconds\n";
	std::cout << "3- 41x41\t 90seconds\n";

	std::cin >> diffSelection;
	difficulty = static_cast<Difficulty>(diffSelection);



	switch (difficulty) {

		case EASY:
			generateMaze(21, 21);

		case NORMAL:
			generateMaze(31, 31);
		
		case HARD:
			generateMaze(41, 41);

	}

	while(!isGameWon) {

	}

}
