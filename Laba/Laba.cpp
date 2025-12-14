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
    setlocale(LC_ALL, "");
    clearScreen();
    while (menu());

	return 0;
}
