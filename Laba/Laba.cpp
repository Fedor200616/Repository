// Laba.cpp: определяет точку входа для приложения.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Laba.h"
#include "function.h"
#include "utility.h"


int main()
{
    SetConsoleCP(1251);       // входная кодировка
    SetConsoleOutputCP(1251); // выходная кодировка
    //_setmode(_fileno(stdout), _O_U8TEXT); // для wcout и русских символов
    //_setmode(_fileno(stdin), _O_U8TEXT);
    setlocale(LC_ALL, "Russian");
    std::locale::global(std::locale("ru_RU.UTF-8"));
    clearScreen();
    while (menu());  
  // std::string name1 = group();
  // std::cout << name1;
  //groupnum();
	return 0;
}
