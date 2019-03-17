#include <iostream>
#include <string>

std::string consonantize(std::string);
bool isConsonant(char);
std::string capitalize(std::string);

int main()
{
	std::string s;

	std::cout << "Please enter a phrase to consonantize: ";
	std::getline(std::cin, s);

	s = consonantize(s);
	s = capitalize(s);

	std::cout << "\n\n" << s;
	std::cin.get();

}

std::string consonantize(std::string s)
{
	if (s.empty())
		return "";

	if (isConsonant(s[0]))
		return s[0] + consonantize(s.substr(1));
	else
		return consonantize(s.substr(1));
}

bool isConsonant(char a)
{
	a = tolower(a);

	if (a == 'a' || a == 'e' || a == 'i' ||
		a == 'o' || a == 'u' || !(isalpha(a)))
		return false;

	return true;
}

std::string capitalize(std::string s)
{
	if (s.empty())
		return "";

	s[0] = toupper(s[0]);

	return s[0] + capitalize(s.substr(1));
}