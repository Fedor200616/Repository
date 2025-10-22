#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include "Laba.h"

bool check_first_char(char c) {
    if (c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}

bool check_char(char c) {
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}

bool check_is_int(char c) {
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

bool check_ref(char c, char ref) {
    if (c == ref)
        return 1;
    else
        return 0;
}

void clearScreen() {
    printf("\033[2J\033[3H");
    //while (getchar() != '\n');
}

void clear_n(char* str) { str[strcspn(str, "\n")] = '\0'; }

bool yorn() {
    bool k;
    char yesno;
    while (true) {
        yesno = getchar();
        while (getchar() != '\n');
        switch(yesno){
        case 'y':
        case 'Y':
            return true;
            break;
        case 'n':
        case 'N':
            return false;
            break;
        default:
            printf("Неверный ввод, допустимо только Y или N\n");
            break;
        }
    }        
    return k;
}

int ynr(){
    bool o = 0;
    char ch;
    while (true){
        ch = getchar();
	while (getchar() != '\n');
        switch(ch){
        case 'n':
        case 'N':
            return 0;
            break;
	case 'y':
        case 'Y':
            return 1;
            break;
        case 'r':
        case 'R':
            return 2;
            break;
        default:
	    printf("Неверный ввод %c, допустимо только Y,N,R\n", ch);
	    break;
        }
    }        
}

bool check_group(std::string name) {
    bool correct_name = 1;
    int i_char = 0;
    if (!check_first_char(name[i_char])) {
        if (check_ref(name[i_char], '_') || check_ref(name[i_char], '\n') || check_ref(name[i_char], ' '))
            return "";
        else correct_name = 0;
    }
    i_char++;
    if (!check_is_int(name[i_char])) correct_name = 0;   //1 7
    i_char++;
    //if (!check_is_int(name[i_char])) i_char++;    //Если факультет >= 10 
    if (!check_first_char(name[i_char])) { //2 O
        if (check_ref(name[i_char], '0')) name[2] = 'O';
        else correct_name = 0;
    }
    i_char++;
    if (!check_ref(name[i_char], '-')) correct_name = 0;    //3 -
    i_char++;
    for (int p = 0; p <= 2; i_char++, p++) {
        if (!check_is_int(name[i_char])) correct_name = 0;  //4-6 206
    }
    if (!check_first_char(name[i_char])) {  //7 B
        correct_name = 0;
    }
    i_char++;    
    if (check_first_char(name[i_char]))
        i_char++;    //8 V
    if (check_ref(name[i_char], '-')) {
        i_char++;
    }
    else {
        i_char++;
        correct_name = 0;
    }
    if (!check_is_int(name[i_char])) correct_name = 0;  //10 2
    i_char++;
    if (!check_is_int(name[i_char])) correct_name = 0;  //11 4
    
    if (!correct_name) {
        printf("Номер группы : %s\n Введено верно? [Y/N]\n", name.c_str());
        correct_name = yorn();
        clearScreen();
    }
    return correct_name;
}

