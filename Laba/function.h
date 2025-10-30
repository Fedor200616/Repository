#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <cstring>

#ifndef FUNCTION_H
#define FUNCTION_H

//function.cpp
FILE* makefile(); // Работа с файлом
void secname();   // Работа с файлом фамилией
void password();  // Работа с файлом пароля
void menu();      // Главное меню
std::string name();   // Ввод фамилии
std::string group();  // Ввод группы
std::string groupnum();   //Ввод номера ученика в группе
std::string enter_password(); // Ввод пароля

#endif
