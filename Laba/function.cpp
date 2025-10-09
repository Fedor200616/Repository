#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <filesystem>
#include "Laba.h"

// Проверь комментарии

bool filename_check(std::string* name) {
    int size = name->length();
    for (int i = 0; i < size; i++) {
        //char c = (*name)[i];
        if (check_first_char((*name)[i]) || check_char((*name)[i]) ||
            check_is_int((*name)[i]) || check_ref((*name)[i], '_') || check_ref((*name)[i], '.') || check_ref((*name)[i], '-')){}
        else{
            printf("\033[1;31mНазвание должно содержать только цифры, латиницу и знак '_'\n\033[0m");
            return 0;
        }
    }
    if ( size > 4 && (*name).substr((*name).size() - 4) == ".txt") return true;
    else {*name += ".txt";
        return 1;}
}

void secname() {
    clearScreen();
    char c_filename[128];
    std::string filename;    
    bool check_true = 0;
    std::string path = "./";
    while (check_true == 0) {
        printf("Доступные файлы:\n");
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if(entry.path().extension() == ".txt"){
                printf("%s \n", entry.path().filename().c_str());
            }
        }
        printf("Введите название .txt файла:\n");
        scanf("%127s", c_filename);
        clear_n(c_filename);
        filename = c_filename;
        clearScreen();
        
        check_true = filename_check(&filename);
    }
    
    FILE *file = fopen(filename.c_str(), "a+");
    
    if (file == NULL){
        printf("Ошибка открытия файла!\n");
        return;
    } else
        printf("Файл %s создан!\n", filename.c_str());
    std::string buffer;
}

void menu() {
    bool k = 0;
    int enter_num = -1;
    while (!k) {
        clearScreen();      
        printf("Выберите тип ввода: \n"
               "1) Ввод Фамилии студента; \n"
               "\033[1;31m2) Ввод пароля студента; INOP \n"
               "3) Просмотр файла Фамилии студента; INOP \n"
               "4) Просмотр файла паролей; INOP \n\033[0m"
               "0) Закрыть программу.\n"); // В будущем сделать проверку ошибок
        
        //std::cin >> enter_num;        
        if(scanf("%i", &enter_num) != 1){
            while (getchar() != '\n');          
            continue;
        }
        //clearScreen();    
        switch (enter_num) {
        case 1:
            //puts("Вызов функции Name");
            secname();
            k = 1;            
            return;
            break;      
            //case 2:
            //puts("Вызов функции Password");
            //k = 1;          
            //break;      
        case 0:
            puts("Вызов функции Endprogramm");
            k = 1;
            return;
            break;
        default:
            puts("Неверный ввод!!!");
            break;
        }
    }
}

std::string name() {
    bool k = 0;
    char c_secname[255];
    std::string secname;
    char yorn;
    clearScreen();
    while (!k) {
        printf("Введите фамилию студента или 0 для выхода в меню \n");
        fgets(c_secname, char_length, stdin);
        clear_n(c_secname);
        c_secname[strcspn(c_secname, "\n")] = '\0';
        clearScreen();
        if (c_secname[0] != '\0') {
            secname = c_secname;
            k = 1;
            for(int i = 0; i < secname.length(); i++){
                if (i == 0 && !check_first_char(secname[i])) {
                    printf("Фамилия должна начинаться на заглавную букву,\n");
                    k = 0;
                } else if (i != 0 && !(check_char(secname[i]) || check_ref(secname[i], '-') || check_ref(secname[i], '_') || check_ref(secname[i], '\''))) {
                    printf("Допустимы только маленькие буквы и знаки -, _, ' \n");
                    k = 0;
                    //std::cout << i << '\t';
                }
            }
            if (!k){
                printf("\033[1;31m%s\n\033[0m", secname.c_str());
                yorn = getchar();
                switch(yorn){
                case 'Y':
                    k = 1;
                    break;
                case 'N':
                    k = 0;
                    break;
                default: k = 0;
                }
            }
        }            
        else {
            clearScreen();
            k = 0;
        }
    }
    return secname;
}
