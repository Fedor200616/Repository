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
            check_is_int((*name)[i]) || check_ref((*name)[i], '_') || check_ref((*name)[i], '.') || check_ref((*name)[i], '-')) {
        }
        else {
            printf("\033[1;31mНазвание должно содержать только цифры, латиницу и знак '_' \033[0m \n");
            return 0;
        }
    }
    if (size > 4 && (*name).substr((*name).size() - 4) == ".txt") return true;
    else {
        *name += ".txt";
        return 1;
    }
}

void namefile() {
    clearScreen();
    char c_filename[char_length];
    std::string filename;    
    bool check_true = 0;
    std::string path = "./";
    while (check_true == 0) {
        printf("Доступные файлы:\n");
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if(entry.path().extension() == ".txt"){
                printf("%ls \n", entry.path().filename().c_str());
            }
        }
        printf("Введите название .txt файла:\n");
        if (fgets(c_filename, char_length - 1, stdin) == NULL) {
            printf("Ошибка ввода!\n");
            continue;
        }
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
    bool file_exit = 0;
    while (!file_exit) {
        buffer = name();
		if (buffer == "0") {
			file_exit = 1;
			clearScreen();
			fclose(file);
			return;
		}
		else {
			fprintf(file, "%s\t", buffer.c_str());
			clearScreen();
			printf("Фамилия %s добавлена в файл! \n", buffer.c_str());
		}
        fprintf(file, "|\t");
        buffer = group();
    }

}

void menu() {
    clearScreen();
    bool wrong_enter = 0;
    bool k = 0;
    char enter_num;
    while (!k) {  
        printf("Выберите тип ввода: \n"
               "1) Ввод Фамилии студента; \n"
               "\033[1;31m2) Ввод пароля студента; INOP \n"
               "3) Просмотр файла Фамилии студента; INOP \n"
               "4) Просмотр файла паролей; INOP \n\033[0m"
               "0) Закрыть программу.\n"); // В будущем сделать проверку ошибок
        
        //std::cin >> enter_num;        
        if(scanf("%c", &enter_num) != 1){
            while (getchar() != '\n');         
            continue;
        }
        clearScreen();
        while (getchar() != '\n');
        switch (enter_num) {
        case '1':     //Вызов функции Name
            namefile();
            k = 1;            
            return;
            break;   
        case '0':
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
                if (check_ref(secname[0], '0')) {
                    k = 1;
                    break;
                }
                else if (i == 0 && !check_first_char(secname[i])) {
                    printf("Фамилия должна начинаться на заглавную букву,\n");
                    k = 0;
                }
                else if (i != 0 && !(check_char(secname[i]) || check_ref(secname[i], '-') || check_ref(secname[i], '_') || check_ref(secname[i], '\''))) {
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

std::string group() {
    char c_name[char_length];
    bool correct_name = 0;
    std::string name;
    while (!correct_name) {
        
        printf("Введите номер группы формата M7O-206BV-24 \n"
                "Вы можете ввести _ для оставления строки пустой\n");
        if (fgets(c_name, char_length - 1, stdin) == NULL) {
            printf("Ошибка ввода!\n");
            continue;
        }
        correct_name = 1;
        name = c_name;
        int i_char = 0;
        if (!check_first_char(name[i_char])) {   //0 M
            if (check_char(name[i_char])) name[i_char] -= 32;
            else if (check_ref(name[i_char], '_')) return "\t\t";
            else correct_name = 0;
        }
        i_char = 1;
        if (!check_is_int(name[i_char])) correct_name = 0;   //1 7
        i_char = 2;
        if (!check_first_char(name[i_char])) { //2 O
            if (check_ref(name[i_char], '0')) name[2] = 'O';
            else correct_name = 0;
        }
        i_char = 3;
        if (!check_ref(name[i_char], '-')) correct_name = 0;    //3 -
        i_char = 4;
        for (; i_char <= 6; i_char++) {
            if (!check_is_int(name[i_char])) correct_name = 0;  //4-6 206
        }
        i_char = 7;
        if (!check_first_char(name[i_char])) {  //7 B
            if (check_char(name[i_char]))  name[i_char] -= 32;
            else correct_name = 0;
        }
        i_char++;
        if (check_first_char(name[i_char])) i_char++;   //8 V
        else if (check_char(name[i_char])) {
            name[i_char] -= 32;
            i_char++;
        }
        if (!check_ref(name[i_char], '-')) correct_name = 0;  //9 -
        i_char++;
        if (!check_is_int(name[i_char])) correct_name = 0;  //10 2
        i_char++;
        if (!check_is_int(name[i_char])) correct_name = 0;  //11 4
    
        if (correct_name) {
            bool n = 0;
            while (!n)
            printf("Номер группы : %s\n Введено верно? Y/N", name.c_str());
            if (getchar() == 'Y') {} // ОСТАНОВИЛИСЬ ЗДЕСЬ
            else if
        }
    }
        



    }
    return name;
}