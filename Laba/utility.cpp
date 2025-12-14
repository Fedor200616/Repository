#define _CRT_SECURE_NO_WARNINGS
#include "utility.h"
#include "Laba.h"
#include "function.h"


bool check_first_char(char c) { // Выводит 1 если буква заглавная, или ноль
    if (c >= 'A' && c <= 'Z')
        return 1;
    else
        return 0;
}

bool check_char(char c) { // Ввыводит 1 если символ - маленькая буква
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}

bool check_is_int(char c) { // Выводит 1 если символ - число
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

bool check_ref(char c, char ref) { // Проверяет 1 аргумент со 2 (референс) и выводит 1 при совпадении
    if (c == ref)
        return 1;
    else
        return 0;
}

void clear_buffer() { // Функция очистки буфера
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen() { // Очистка экрана
    system("cls");
}

void clear_n(char* str) { str[strcspn(str, "\n")] = '\0'; } // Убирает \n из строки

bool yorn() { // Функция вопроса у пользователья Да или нет, выводит 1 при Y и 0 при N
    bool k = false;
    unsigned char yesno;
	int n = 0;
    while (n < 10) {
        yesno = _getch();
        printf("\n");
        switch(yesno){
        case 'y':
        case 'Y':
        case 'н':
		case 'Н':
            return true;
            break;
        case 'n':
        case 'N':
		case 'т':
		case 'Т':
            return false;
            break;
        default:
            printf("Неверный ввод, допустимо только Y или N\n");
            break;
        }
		if (++n >= 10) {
            clearScreen();
			printf("Превышено количество попыток ввода, возврат к вводу\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            k = false;
			return false;
		}
    }        
	
    return k;
}


int ynrs(){ // Функция ответа на вопрос Нет/Да/Вернуться/Вернуться с сохранением , выводит 0 на N, 1 - Y,
    bool o = 0;
    char ch;
    while (true){
        ch = _getch();
        printf("\n");
	    //while (getchar() != '\n'){};
        switch(ch){
        case 'n':
        case 'N':
        case 'т':
        case 'Т':
            return 0;
            break;
		case 'y':
		case 'Y':
		case 'н':
		case 'Н':
        case '\r':
            return 1;
            break;
        case 'r':
        case 'R':
        case 'к':
        case 'К':
            return 2;
            break;
        case 's':
        case 'S':
        case 'ы':
        case 'Ы':
            return 3;
            break;
        default:
	        printf("Неверный ввод %c, допустимо только Y,N,R\n", ch);
	        break;
        }
    }        
}

bool filename_check(std::string* name) {    //Функция проверяет введенное имя файла
    int size = name->length();
    for (int i = 0; i < size; i++) {
        //char c = (*name)[i];
        if (check_first_char((*name)[i]) || check_char((*name)[i]) || RU_check_first_char((*name)[i]) || RU_check_char((*name)[i]) ||
            check_is_int((*name)[i]) || check_ref((*name)[i], '_') || check_ref((*name)[i], '.') || check_ref((*name)[i], '-')) {
        }
        else {
            printf("\033[1;31mНазвание должно содержать только цифры, буквы и знаки '_' '.' '-' \033[0m \n");
            return 0;
        }
    }
    if (size > 4 && (*name).substr((*name).size() - 4) == ".txt") return true;     //Добавляем .txt, если ее не ввел пользователь
    else {
        *name += ".txt";
        return 1;
    }
}

bool check_group(std::string name) { // Нужна только для group Проверяет соответсвие типовому имени группы
    bool correct_name = 1;
    int i_char = 0;
    if (name.length() == 1){
        if (check_ref(name[0], '_') || check_ref(name[0], '\0')){
            return 1;
        }
    }
    for (int i = 0; i < name.length(); i++){
        if (check_first_char(name[i]))
            ;
        else if (check_char(name[i]))
            ;
        else if (RU_check_first_char(name[i]))
            ;
        else if (RU_check_char(name[i]))
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

bool RU_check_first_char(unsigned char c) { // Выводит 1 если буква - русская заглавная, или ноль
	//printf("%c : %d\n", c, c); // debug
    if (c >= 192 && c <= 222 || c == 168)
        return 1;
    else return 0;
	//return 1;
}

bool RU_check_char(unsigned char c) { // Ввыводит 1 если символ - маленькая русская буква
    //printf("%c : %d\n", c, c); //debug
    if (c >= 223 && c <= 255 || c == 184)
        return 1;
    else return 0;
}

