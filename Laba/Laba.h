// Laba.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <cstring>

#ifndef HEADER_H
#define HEADER_H

//utility.cpp
const int char_length = 255;
bool check_first_char(char c); // Выводит 1 если буква заглавная, или ноль
bool check_char(char c); // Ввыводит 1 если символ - маленькая буква
bool check_is_int(char c); // Выводит 1 если символ - число
bool check_ref(char c, char ref); // Проверяет 1 аргумент со 2 (референс) и выводит 1 при совпадении
void clearScreen(); // Очистка экрана
void clear_n(char* str); // Убирает \n из строки
bool filename_check(std::string* name); // Проверка имени файла на валидность

//function.cpp
void namefile(); // Работа с файлом фамилии
void menu(); // Главное меню
std::string name(); // Ввод фамилии
std::string group(); // Ввод группы

#endif
