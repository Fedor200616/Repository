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
