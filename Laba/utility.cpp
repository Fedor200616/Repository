

#include "utility.h"
#include "Laba.h"
#include "function.h"
#include "settings.h"

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
	while (getchar() != '\n'){};
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
    if (name.length() == 1){
        if (check_ref(name[0], '_') || check_ref(name[0], ' ') || check_ref(name[0], '\0')){
            return 1;
        }
        else if (check_ref(name[0], '0')){
            return 1;
        }
    }
    for (int i = 0; i < name.length(); i++){
        if (check_first_char(name[i]))
            ;
        else if (check_char(name[i]))
            ;
        else if (check_is_int(name[i]))
            ;
        else if (check_ref(name[i], '-') || check_ref(name[i], '_'))
            ;
        else correct_name = 0;
      
    }
    if (!correct_name) {
        printf("Номер группы : %s\n Введено верно? [Y/N]\n", name.c_str());
        correct_name = yorn();
        clearScreen();
    }
    return correct_name;
}

