#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <conio.h>
//#include <filesystem>
#include <windows.h>

#ifndef UTILITY_H
#define UTILITY_H
//utility.cpp
const char RU_AZ[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const char RU_az[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

bool check_first_char(char c); // Выводит 1 если буква заглавная, или ноль
bool check_char(char c); // Ввыводит 1 если символ - маленькая буква
bool check_is_int(char c); // Выводит 1 если символ - число
bool check_ref(char c, char ref); // Проверяет 1 аргумент со 2 (референс) и выводит 1 при совпадении
void clearScreen(); // Очистка экрана
void clear_n(char* str); // Убирает \n из строки
bool yorn(); // Функция вопроса у пользователья Да или нет, выводит 1 при Y и 0 при N
int ynr(); // Функция ответа на вопрос Нет/Да/Вернуться , выводит 0 на N, 1 - Y,
           // 2 - R
bool filename_check(std::string* name); // Проверяет имя файла на ссответсвие требованиям
bool check_group(std::string name); // Нужна только для group Проверяет
                                    // соответсвие типовому имени группы
bool RU_check_first_char(char c); // Выводит 1 если буква - русская заглавная, или ноль
bool RU_check_char(char c); // Ввыводит 1 если символ - маленькая русская буква
bool is_txt(const std::string& filename); // Проверяет расширение файла на .txt

#endif
