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
void clearScreen();
void clear_n(char* str);

//function.cpp
void secname();
void menu();
std::string name();
int secname_check(std::string str); //* @secname_check Выводится 1 при правильности ввода, 2 при неправильном вводе

#endif
