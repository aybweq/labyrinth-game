#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <random>
#include <algorithm>


bool isAvailable(int width, int height, int nx, int ny, const std::vector<std::vector<bool>>& visited) {

	if(nx >= 0 && nx < width && ny >= 0 && ny < height) {
		if(visited[ny][nx] == false) {
			return true;
		}
	}

	return false;

}


std::vector<std::vector<char>> generateMaze(int width, int height) {

	// maze as 2d vector
	std::vector<std::vector<char>> maze(height, std::vector<char>(width, '#'));

	// stack for randomized dfs
	// holds x,y coordinates
	std::stack<std::pair<int, int>> stack;


	std::vector<std::pair<int, int>> Directions {
		{1, 0}, 	// right
		{-1, 0}, 	// left
		{0, 1},	 // down
		{0, -1} 	// up
	};

	// generating random number
	std::random_device rd;
	std::mt19937 gen(rd());


	// starting point
	maze[0][0] = ' ';
	stack.push({0, 0});

	// tracking visited cells
	std::vector<std::vector<bool>> visited (height, std::vector<bool>(width, false));
	visited[0][0] = true;

	std::pair<int, int> randomDir;


	// shuffle olayini duzelt
	// stack push ve pop olayini hallet
	// hangi cell'ler yola cevrilecek?

	while(!stack.empty()) {

		// current coordinates
		int cx {stack.top().first};
		int cy {stack.top().second};

		// shuffling 
		std::shuffle(Directions.begin(), Directions.end(), gen);

		bool foundNeighbour = false;

		for(const auto& dir: Directions) {

			// next coordinates
			int nx {cx + dir.first * 2};
			int ny {cy + dir.second * 2};

			if(isAvailable(width, height, nx, ny, visited)) {

				// middle cell
				int mx {(cx + nx)/2};
				int my {(cy + ny)/2};

				// convert cells to road
				maze[my][mx] = ' ';
				maze[ny][nx] = ' ';

				visited[ny][nx] = true;

				stack.push({nx, ny});
				foundNeighbour = true;

				break;
			}
		}

		if(!foundNeighbour) {
			stack.pop();
		}

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

	auto maze = generateMaze(21, 21);
	printMaze(maze);

}
