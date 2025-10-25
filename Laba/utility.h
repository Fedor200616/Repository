#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <filesystem>

#ifndef UTILITY_H
#define UTILITY_H

//utility.cpp
bool check_first_char(char c); // Выводит 1 если буква заглавная, или ноль
bool check_char(char c); // Ввыводит 1 если символ - маленькая буква
bool check_is_int(char c); // Выводит 1 если символ - число
bool check_ref(char c, char ref); // Проверяет 1 аргумент со 2 (референс) и выводит 1 при совпадении
void clearScreen(); // Очистка экрана
void clear_n(char* str); // Убирает \n из строки
bool yorn(); // Функция вопроса у пользователья Да или нет, выводит 1 при Y и 0 при N
int ynr(); // Функция ответа на вопрос Нет/Да/Вернуться , выводит 0 на N, 1 - Y,
           // 2 - R
bool check_group(std::string name); // Нужна только для group Проверяет
                                    // соответсвие теповому имени группы

#endif
