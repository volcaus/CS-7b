#include <iostream>
#include <string>
#include <limits>

std::string recSequence(std::string, int);
std::string generate(std::string, int);
void error(int);

int main()
{
	int order = -1;
	std::string sequence;

	while (order < 0 || order > 20)
	{
		std::cout << "What order would you like the sequence "
			<< "to be: ";
		std::cin >> order;

		if (order <= 0 || std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			order = 0;
			error(0);
		}
	}
	
	while (sequence != "A" && sequence != "B")
	{
		std::cout << "A or B sequence: ";
		std::cin >> sequence;
		sequence[0] = toupper(sequence[0]);

		if ((sequence[0] != 'A' && sequence[0] != 'B')
					|| std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			sequence = 'C';
			error(1);
		}
	}

	std::cout << sequence << "-Sequence: " << recSequence(sequence, order);
	
}

std::string recSequence(std::string a, int n)
{
	if (n < 0)
		return "";
	
	a = generate(a, a.size()-1);

	return recSequence(a, n-1);

}

std::string generate(std::string str, int n)
{
	if (n < 0)
		return "";
	
	if (str[n] == 'A')
		str.push_back('B');
	else
		str.push_back('A');

	return generate(str, n-1);
}

void error(int q)
{
	if (q == 0)
	{
		std::cout << "\nIncorrect value input. Please enter a positive integer "
		<< "value for the desired order.\n";
	}
	else 
		std::cout << "\nPlease enter 'A' or 'B'.\n";
}
