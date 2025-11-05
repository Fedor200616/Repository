// Laba.cpp: определяет точку входа для приложения.
//
#include "Laba.h"
#include "function.h"
#include "utility.h"
#include "settings.h"


int main()
{
  // setlocale(LC_ALL, "Russian");
  // std::locale::global(std::locale("ru_RU.UTF-8"));
    clearScreen();
    while (menu());  
  // std::string name1 = group();
  // std::cout << name1;
  //groupnum();
	return 0;
}
