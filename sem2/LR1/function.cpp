#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string>
//#include <cstdlib>

const int char_length = 255;

//Проверь комментарии

void clearScreen();
void clear_n(char *str);

void menu();
void name();
int secname_check(std::string str); //* @secname_check Выводится 1 при правильности ввода, 2 при неправильном вводе

int main() {
    clearScreen();  
    //name();  
    menu();
    return 0;
}

void clearScreen(){
    printf("\033[2J\033[3H");
    //while (getchar() != '\n');
}

void clear_n(char* str){
    str[strcspn(str, "\n")] = '\0';
}

void menu() {
    int enter_num;
    printf("Выберите тип ввода: \n"
           "1) Ввод Фамилии студента; \n"
           "2) Ввод пароля студента; \n"
           "0) Закрыть программу.\n"); // В будущем сделать проверку ошибок
    fflush(stdin);
    scanf("%i", &enter_num);
    clearScreen();    
    switch (enter_num) {
    case 1:
        //puts("Вызов функции Name");
        name();      
        break;      
    case 2:
        puts("Вызов функции Password");
        break;      
    case 0:
        puts("Вызов функции Endprogramm");      
        break;
    }
   
}

void name() {
    bool k = 0; // Значение правильности ввода фамилии
    char secname[255];
    std::string s_secname;
    while (!k) {
        printf("Введите фамилию студента или 0 для выхода в меню \n");
        fgets(secname, char_length, stdin);
        clear_n(secname);
        //secname[strcspn(secname, "\n")] = '\0';        
        if (secname[0] != '\0') {
            s_secname = secname;
            switch (secname_check(s_secname)) {
            case 0:
                clearScreen();              
                menu();
                break;              
            case 1:
                // puts(s_secname.c_str());
                clearScreen();
                std::cout << s_secname << "\n";
                break;                
            }
        }            
        else {
            clearScreen();
            k = 0;
            //choose_enter_type();//Вообще нужно проверять на возможные ошибки
        }
    }
}

int secname_check(std::string str){
    if (str == "0" || str == "o" || str == "о" || str == "О" || str == "O"){
        return 0;
    }
    else{return 1;}    
    return 1;    
}
