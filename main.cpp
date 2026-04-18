#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>


bool isCellAvailable(int width, int height, int nx, int ny, const std::vector<std::vector<bool>>& visited) {

	if(nx >= 0 && nx < width && ny >= 0 && ny < height) {
		if(visited[ny][nx] == false) {
			return true;
		}
	}

	return false;

}

std::vector<std::vector<char>> generateMaze(int width, int height, std::pair<int, int> playerPos) {

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
	maze[playerPos.first][playerPos.second] = ' ';
	stack.push({playerPos.first, playerPos.second});

	// tracking visited cells
	std::vector<std::vector<bool>> visited (height, std::vector<bool>(width, false));
	visited[playerPos.second][playerPos.first] = true;


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

			if(isCellAvailable(width, height, nx, ny, visited)) {

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

	maze[playerPos.second][playerPos.first] = 'P';
	
	return maze;

}

void printMaze(const std::vector<std::vector<char>>& maze, int time_left) {

	const std::string RED = "\033[1;31m";
	const std::string GREEN = "\033[1;32m";
	const std::string RESET = "\033[0m";

	// clear screen
	std::cout << "\033[2J\033[H";

	// print top borders
	std::cout << RED << std::string(maze[0].size() + 2, '@') << RESET;
	std::cout << '\n';
	
	// print maze
	for(int i = 0; i < maze.size(); i++) {

		// print left borders
		std::cout << RED << '@' << RESET;
		
		for(int j = 0; j < maze[0].size(); j++) {
			std::cout << maze[i][j];
		}

		// print right borders
		std::cout << RED << '@' << RESET;
		std::cout << '\n';
	}

	// print bottom borders
	std::cout << RED << std::string(maze[0].size() + 2, '@') << RESET;
	std::cout << '\n';

	// go to time column
	int timeColumn = maze[0].size() + 7; 
	std::cout << "\033[1;" << timeColumn << "H";

	//print time left
	std::cout << "TIME LEFT: " << time_left;

	// idk
	std::cout << "\033[" << maze.size() + 4 << ";1H" << std::flush;
}

bool targetPointReached(const std::vector<std::vector<char>>& maze) {
	if(maze[maze.size() - 1][maze[0].size() - 1] == 'P') return true;

	return false;
}

void movePlayer(std::vector<std::vector<char>>& maze, std::pair<int, int>& playerPos, int movement, int width, int height) {

	std::vector<std::pair<int, int>> Directions {
		{1, 0}, 	// right
		{-1, 0}, 	// left
		{0, 1},	 // down
		{0, -1} 	// up
	};

	// wanted direction
	int movementX = Directions[movement].second;
	int movementY = Directions[movement].first;

	// wanted cell
	int xToGo = playerPos.first + movementX;
	int yToGo = playerPos.second + movementY;

	// if cell is not out of bounds and not a wall, move player
	if(xToGo >= 0 && xToGo < width && yToGo >= 0 && yToGo < height) {

		if(maze[yToGo][xToGo] != '#') {

			// movement
			maze[yToGo][xToGo] = 'P';
			maze[playerPos.second][playerPos.first] = ' ';

			// update playerPos
			playerPos.first = yToGo;
			playerPos.second = xToGo;
		}
	}
}

int main() {

	// yon tuslari ata
	// mumkunse oyuncuyu hareket ettir

	int time_limit = 5;

	const int ticks_per_second = 24;
	const std::chrono::nanoseconds skip_ticks(1000000000 / ticks_per_second);

	std::chrono::steady_clock::time_point next_tick = std::chrono::steady_clock::now();
	auto start_time = next_tick;

	int width = 61;
	int height = 31;

	// playerPos is: (y, x)
	std::pair<int, int> playerPos {0, 0};
	auto maze = generateMaze(width, height, playerPos);
	// maze size must be odd numbers or it will crash


	while(!targetPointReached(maze)) {

		std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
		auto elapsed = current_time - start_time;

		int seconds_past = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
		int time_left = time_limit - seconds_past;


		printMaze(maze, time_left);

		if(time_left < 0) {
			break;
		}


		// waiting until end of the tick
		next_tick += skip_ticks;
		std::this_thread::sleep_until(next_tick);

		movePlayer(maze, playerPos, 0, width, height);
	}

	if(targetPointReached(maze)) std::cout << "You won!\n";
	else std::cout << "You lost!\n";

}