#include <iostream>
#include <vector>
#include <stack>
#include <utility>

// # -> wall
// ' ' -> empty space
// $ -> player

typedef enum Difficulty {
	EASY = 1,
	NORMAL,
	HARD,
	CUSTOM
} Difficulty;


std::vector<std::vector<char>> generateMaze(int width, int height) {

	// maze as 2d vector
	std::vector<std::vector<char>> maze(height, std::vector<char>(width, '#'));

	// stack for randomized dfs
	// holds x,y coordinates
	std::stack<std::pair<int, int>> stack;


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
	std::cout << "1- 20x20\t 150seconds\n";
	std::cout << "2- 30x30\t 120seconds\n";
	std::cout << "3- 40x40\t 90seconds\n";
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

}
