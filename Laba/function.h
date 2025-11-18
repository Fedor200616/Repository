#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <Windows.h>
#include <filesystem>


#ifndef FUNCTION_H
#define FUNCTION_H

//function.cpp
FILE* makefile(); // Работа с файлом
void secname();   // Работа с файлом фамилией
void password();  // Работа с файлом пароля
int menu();      // Главное меню
std::string name();   // Ввод фамилии
std::string group();  // Ввод группы
std::string groupnum();   //Ввод номера ученика в группе
std::string enter_password(); // Ввод пароля
void instruction();

#endif
