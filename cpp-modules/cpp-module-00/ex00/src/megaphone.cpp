
#include <iostream>
#include <string>
#include <algorithm>

void printUpper(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string str = argv[i];
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		std::cout << str;
		if (i < argc - 1)
			std::cout << " ";
	}
}

int main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
		printUpper(argc, argv);
	std::cout << std::endl;
	return 0;
}
