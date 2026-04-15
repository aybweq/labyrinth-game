#include <iostream>
#include <vector>
#include <cstdlib>

typedef enum Difficulty {
	EASY = 1,
	NORMAL,
	HARD,
	CUSTOM
} Difficulty;

void generateMaze(int width, int height) {

}

void printMaze(int mapSize) {
	
		std::cout << std::string(mapSize+2, '@');
		std::cout << '\n';
		for(int i = 0; i < mapSize; i++) {
			std::cout << '@';
			std::cout << std::string(mapSize, ' ');
			std::cout << '@';
			std::cout << '\n';
		}
		std::cout << std::string(mapSize+2, '@');
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
		generateMaze(20, 20);

    case NORMAL:
		generateMaze(30, 30);
		
    case HARD:
		generateMaze(40, 40);

	}
	system("clear");
}
