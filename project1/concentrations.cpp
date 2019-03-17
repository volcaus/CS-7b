#include <iostream>
#include <vector>
#include <limits>

typedef std::vector<std::vector<int>> Grid;

void printWorld(Grid, int, int, int);
void dropUnit(Grid&, int, int);
void diffuse(Grid&, int, int);
void checkWorld(Grid&, int);
Grid generate(Grid&, int, int, int);

int main()
{
	int level;
	int size;
	Grid world;
	
	int row, column; // For use in placing units

	std::cout << "What level would you like this world to be (0-4): ";
	std::cin >> level;

	while (level < 0 || level > 4 || std::cin.fail())
	{
		std::cout << "\nIncorrect input, enter a level (0-4): ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		std::cin >> level;
	}

	std::cout << "\nHow big would you like the world to be (3-10): ";
	std::cin >> size;

	while (size < 3 || size > 10 || std::cin.fail())
	{
		std::cout << "\nIncorrect input, enter a size (3-10): ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
		std::cin >> size;
	}
	
	world = generate(world, level, size-1, size);

	while(true)
	{
		std::cout << std::endl << std::endl;
		printWorld(world, 0, 0, size);

		
	}
}

void printWorld(Grid world, int b, int m, int n)
{
	if (b = n)	// Return after printing final row
		return;

	std:: cout << world[b][m] << " ";
	
	if (m < n)	// Move to next column if row unfinished
		printWorld(world, b, m+1, n);

	std::cout << std::endl;	// Begin next row

	printWorld(world, b+1, 0, n);
}

void dropUnit(Grid& world, int row, int col)
{

}

Grid generate(Grid& world, int lvl, int n, int size)
{
	if (n == 0)		// Return finished world
		return world;
	if (world.empty());
		world.resize(size);
	if (world[n].empty())
		world[n].resize(size);

	
	world[n][n-1] = lvl;
	world[n-1][n] = lvl;

	return generate(world, lvl, n-1, size);
}
