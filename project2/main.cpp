/* CLEAN UP NOTES
*
* sizing of Grid
* printing and allocating of Grid
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

typedef std::vector<std::vector<std::string> > Grid;

bool isWord(std::string, bool);	// Checks if a vector<string>(3) is in the included 6-letter wordlist
Grid genChemWords(std::vector<std::string>, bool);	// Used with the above function to make a 2d vector<string> of 6 letter words composed of chem symbols
void populateSymbols(std::vector<std::string>&);	// Puts 48 chem symbols into a vector<string>
Grid populateGrid(Grid, Grid);	// Uses the generated chemWords to make a 2d vector<string> in a 3x3 grid so that every row and column is a unique chemword
std::string printGrid(Grid, int, int = 0);	// Prints the result of above function
bool isChemWord(std::string, Grid, int = 3);	// Checks if a concatenation of 3 chem symbols is in the given wordlist
void clearGrid(Grid&);	// Empties any 2d vector<string>
bool notUsed(Grid, std::vector<std::string>);	// Checks if a given chemWord is already used in the 3x3 grid

int main()
{
	std::vector<std::string> symbols;
	Grid g(3, std::vector<std::string>(3)), chemWords;
	bool fileCheck = 0;

	populateSymbols(symbols);

	std::ifstream inFile("chemWords.txt");

	std::cout << "Please wait while the chemWords "
		<< "are populated...\n";

	if (inFile.good())
	{
		std::cout << "Existing file found, checking chemWords...\n";
		inFile.close();
		fileCheck = 1;
	}
	else
	{
		std::cout << "No existing file found, generating chemWords from scratch...\n";
		inFile.close();
	}

	chemWords = genChemWords(symbols, fileCheck);

	std::cout << "Working on a solution...\n";

	g = populateGrid(g, chemWords);

	std::cout << std::endl << printGrid(g, g.size());

	std::cin.get();

	return 0;
}

Grid genChemWords(std::vector<std::string> vec, bool fileCheck)	// Takes vector<string> with the 48 chem symbols as parameter
{
	Grid chemW;
	std::vector<std::string> chemVec(3);

	for (auto i : vec)
	{
		for (auto j : vec)
		{
			for (auto k : vec)
			{
				if (isWord(i + j + k, fileCheck))
				{
					chemVec[0] = i;
					chemVec[1] = j;
					chemVec[2] = k;

					chemW.push_back(chemVec);
					std::cout << i + j + k << std::endl;
				}
			}
		}
	}

	return chemW;
}

bool isWord(std::string word, bool fileCheck)
{
	std::ifstream inFile;

	if (fileCheck == 0)
		inFile.open("sixLetter.txt");
	else
		inFile.open("chemWords.txt");

	std::string t;
	while (inFile >> t)
	{
		if (word == t)
		{
			inFile.close();
			return true;
		}
	}
	inFile.close();
	return false;
}

bool isChemWord(std::string str, Grid g, int condition)
{
	switch (condition)
	{
	case 2:
		for (auto i : g)
			if (str == i[0] + i[1])
				return true;

	case 3:
		for (auto i : g)
			if (str == i[0] + i[1] + i[2])
				return true;
	default:
		break;
	}
	return false;
}

void clearGrid(Grid& g)
{
	for (size_t i = 0; i < g.size(); ++i)
	{
		g[i].clear();
		g[i].resize(3);
	}
}

bool notUsed(Grid used, std::vector<std::string> word)
{
	for (auto i : used)
		if (i == word)
			return false;

	return true;
}

Grid populateGrid(Grid g, Grid chemW)
{
	Grid samesies0, samesies1, samesies2;
	bool jobDone = false;
	Grid used;

	do // Desperate times :^)
	{
		clearGrid(g);
		clearGrid(used);

		for (auto i : chemW)	// First row (random)
		{
			g[0] = i;
			used.push_back(i);

			samesies0.clear();
			for (auto j : chemW)
				if (j[0] == g[0][0])
					samesies0.push_back(j);

			if (samesies0.empty())
				continue;

			for (auto k : samesies0)	// First column (based on first element
				if (k != g[0])			// of first row)
				{
					g[1][0] = k[1];
					g[2][0] = k[2];
					used.push_back(k);

					samesies1.clear();
					for (auto l : chemW)
						if (l[0] == g[0][1])
							samesies1.push_back(l);

					if (samesies1.empty())
						continue;

					for (auto m : samesies1)
						if (g[1][0] != m[1] && g[2][0] != m[2] &&
							isChemWord(g[1][0] + m[1], chemW, 2) &&
							isChemWord(g[2][0] + m[2], chemW, 2) &&
							notUsed(used, m))// Second column (based on second element of first row)
						{
							g[1][1] = m[1];
							g[2][1] = m[2];
							used.push_back(m);

							samesies2.clear();
							for (auto n : chemW)
								if (n[0] == g[0][2])
									samesies2.push_back(n);

							if (samesies2.empty())
								continue;

							for (auto o : samesies2)
								if (isChemWord(g[1][0] + g[1][1] + o[1], chemW) &&
									isChemWord(g[2][0] + g[2][1] + o[2], chemW) &&
									(g[1][1] != o[1]) && (g[2][1] != o[2]) &&
									notUsed(used, o))
								{
									g[1][2] = o[1];
									g[2][2] = o[2];
									jobDone = true;
									return g;
								}
						}

				}
		}
	} while (!jobDone);
	return g;
}


std::string printGrid(Grid g, int size, int n)
{
	if (n == size)
		return "";

	std::string str = g[n][0] + " " + g[n][1] + " " + g[n][2] + "\n";

	return str += printGrid(g, size, n + 1);
}

void populateSymbols(std::vector<std::string>& CS)
{
	CS.push_back("he"); CS.push_back("ac"); CS.push_back("al"); CS.push_back("am");
	CS.push_back("ar"); CS.push_back("as"); CS.push_back("at"); CS.push_back("ba");
	CS.push_back("be"); CS.push_back("bi"); CS.push_back("br"); CS.push_back("ca");
	CS.push_back("ce"); CS.push_back("cl"); CS.push_back("co"); CS.push_back("es");
	CS.push_back("er"); CS.push_back("fr"); CS.push_back("ga"); CS.push_back("ge");
	CS.push_back("au"); CS.push_back("ha"); CS.push_back("he"); CS.push_back("ho");
	CS.push_back("in"); CS.push_back("ir"); CS.push_back("fe"); CS.push_back("la");
	CS.push_back("li"); CS.push_back("mo"); CS.push_back("ne"); CS.push_back("ni");
	CS.push_back("no"); CS.push_back("po"); CS.push_back("pr"); CS.push_back("pa");
	CS.push_back("ra"); CS.push_back("re"); CS.push_back("se"); CS.push_back("si");
	CS.push_back("ag"); CS.push_back("na"); CS.push_back("ta"); CS.push_back("te");
	CS.push_back("th"); CS.push_back("ti"); CS.push_back("te"); CS.push_back("sc");
}
