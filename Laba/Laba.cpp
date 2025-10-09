// Laba.cpp: определяет точку входа для приложения.
//

#include "Laba.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	std::locale::global(std::locale("ru_RU.UTF-8"));
	clearScreen();
	//menu();
	std::string name1 = group();
	std::cout << name1;
	return 0;
}
