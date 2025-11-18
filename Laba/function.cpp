#define _CRT_SECURE_NO_WARNINGS
#include "Laba.h"
#include "function.h"
#include "utility.h"

#include <codecvt>
#include <cwctype>


FILE* makefile() {     //Основная функция для работы с файлом с фамилиями
    clearScreen();
    char c_filename[char_length];
    std::string filename;    
    bool check_true = 0;
    std::string path = "myfiles";
    
    while (check_true == 0) {    // Выводим в cmd файлы с расширением .txt
        printf("Доступные файлы:\n");
		WIN32_FIND_DATAA fileData;
        HANDLE hFind = FindFirstFileA((path + "\\*.txt").c_str(), &fileData);
        //if (hFind == INVALID_HANDLE_VALUE) {
        //    printf("\033[1;31mНе удалось открыть директорию\033[0m\n");
        //    return nullptr;
        //}
		do {
			std::string fname = fileData.cFileName;
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				if (is_txt(fname))
				    printf("%s\n", fname.c_str());
			}
		} while (FindNextFileA(hFind, &fileData));
        FindClose(hFind);
        printf("===============================================\n");

        printf("Введите название .txt файла:\n");    // Пользователь вводит имя его файла, мы его проверяем и создаем файл с его именен
        if (fgets(c_filename, char_length - 1, stdin) == NULL) {
            printf("\033[1;31mОшибка ввода!\n\033[0m");
            continue;
        }
        clear_n(c_filename);
        if (c_filename[0] != '\0') {
            filename = c_filename;
            clearScreen();
            check_true = filename_check(&filename);
        }
        else clearScreen();
    }
	
    FILE* file = fopen((path + "/" + filename).c_str(), "a+");

    if (!file){
        printf("\033[1;31mОшибка открытия файла!\n\033[0m");
        
        return nullptr;
    } else {
        printf("Файл %s успешно открыт!\n", filename.c_str());
        return file;
    }    
}

void secname() {
    printf("Выберите файл с фамилиями\n");
    FILE *file = makefile();
    if (!file){
        printf("\033[1;31mОшибка открытия файла!\033[0m\n");
        //menu();
        return;
    }
    struct Secname_struct{
        std::string buffer_secname;
        std::string buffer_group;
        std::string buffer_num;
    };
    struct Secname_struct sn;
    
    bool file_exit = 0;
    while (!file_exit) {
        sn.buffer_secname = name();
        if (sn.buffer_secname == "0") {
            file_exit = 1;
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
        else {
            clearScreen();
            printf("Фамилия студента %s \n", sn.buffer_secname.c_str());
        }
        sn.buffer_group = group();
        clearScreen();
        if (sn.buffer_group == "0"){
            printf("Возврат к выбору фамилии\n");
            continue;
        }
        printf("Номер группы %s \n", sn.buffer_group.c_str());
        sn.buffer_num = groupnum();
        clearScreen();
        printf("Записать данные студента\n"
               "| %-12s | %-12s | %-5s|\n"
               "[Y/N/R для выхода в меню]\n",
               sn.buffer_secname.c_str(), sn.buffer_group.c_str(), sn.buffer_num.c_str());
        int k = ynr();
	clearScreen();
        if (k == 1) {
            fprintf(file, "| %-12s | %-12s | %-5s |\n", sn.buffer_secname.c_str(),
                    sn.buffer_group.c_str(), sn.buffer_num.c_str());
            printf("Данные успешно записаны!\n");
        }
        else if (k == 2) {
            file_exit = 1;
            fprintf(file,"\n");
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
    }
}

void password() {
    printf("Выберите файл паролей\n");
    FILE *file = makefile();
    if (!file){
        printf("\033[1;31mОшибка открытия файла!\n\033[0m");
        //menu();
        return;
    }
    struct Password_struct{
        std::string buffer_password;
        std::string buffer_group;
        std::string buffer_num;
    };
    struct Password_struct pw;
    int file_exit = 0;
    while(!file_exit){
        pw.buffer_password = enter_password();
        if (pw.buffer_password == "0") {
            file_exit = 1;
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
        else {
            clearScreen();
            printf("Пароль студента %s \n", pw.buffer_password.c_str());
        }
        pw.buffer_group = group();
        clearScreen();
        if (pw.buffer_group == "0"){
            printf("Возврат к выбору пароля");
            continue;
        }
        printf("Номер группы %s \n", pw.buffer_group.c_str());
        pw.buffer_num = groupnum();
        clearScreen();
        printf("Записать данные студента\n"
               "| %-20s | %-12s | %-5s|\n"
               "[Y/N/R для выхода в меню]\n",
               pw.buffer_password.c_str(), pw.buffer_group.c_str(), pw.buffer_num.c_str());
        int k = ynr();
	clearScreen();
        if (k == 1) {
            fprintf(file, "| %-20s | %-12s | %-5s |\n", pw.buffer_password.c_str(),
                    pw.buffer_group.c_str(), pw.buffer_num.c_str());
            printf("Данные успешно записаны!\n");
        }
        else if (k == 2) {
            file_exit = 1;
            fprintf(file,"\n");
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
    }
}

int menu() {
    clearScreen();
    bool wrong_enter = 0;
    bool k = 0;
    char enter_num;
    while (!k) {
        printf("Выберите тип ввода: \n"
               "1) Ввод фамилии студента; \n"
               "2) Ввод пароля студента;\n"
               "3) Инструкция пользователю;\n"
               "0) Закрыть программу.\n"); // В будущем сделать проверку ошибок
        
        //std::cin >> enter_num;        
        enter_num = _getch();
        printf("\n");
        clearScreen();
        //while (getchar() != '\n');
        switch (enter_num) {
        case '1':     //Вызов функции Name
            secname();
            k = 1;            
            break;
        case '2':
            password();
            k = 1;
            break;
        case '3':
            instruction();
            break;
        case '0':
            return 0;
            k = 1;
            break;
        default:
            puts("Неверный ввод!!!");
            break;
        }
    }
    return 1;
}

std::string name() {
    bool k = 0;
    char c_secname[255];
    std::string b_secname;
    std::string secname;
    clearScreen();
    while (!k) {
        printf("Введите фамилию студента или 0 для выхода в меню \n");
        c_secname[0] = '\0';
        fgets(c_secname, char_length - 1, stdin);
        clear_n(c_secname);
        clearScreen();
        if (c_secname[0] != '\0') {
            secname = c_secname;
            k = 1;
            for(int i = 0; i < secname.length(); i++){
                if (check_ref(secname[0], '0') && secname.length() == 1) {
                    k = 1;
                    return "0";
                    break;
                }                    
                else if (k == 1 && (i != 0 && !((check_char(secname[i]) || RU_check_char(secname[i]) || check_ref(secname[i], '-') || check_ref(secname[i], '_') || check_ref(secname[i], '\''))))) {
                    printf("Допустимы только маленькие буквы и знаки -, _, ' \n");
                    k = 0;
                }
            }
            if (!k){
                printf("\033[1;31m%s\033[0m\n"
                       "Вы уверены в правильности ввода?\n"
                       "[Y/N]\n", secname.c_str());
                k = yorn();
                clearScreen();
            }
            if (!(check_first_char(secname[0]) || RU_check_first_char(secname[0]) && k == 1)) {
                printf("Фамилия должна начинаться на заглавную букву,\n");
                if (check_char(secname[0])) {
                    b_secname = secname;
                    b_secname[0] -= Aa;
                    printf("Вы имели ввиду %s?\n"
                           "[Y/N]\n",
                           b_secname.c_str());
                    k = yorn();
                    if (k) {
                        secname = b_secname;
                    }
                    else k = 1;
                }
                else k = 0;
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
            "Вы можете ввести _ для оставления строки пустой или 0 для возврата назад\n");
        fgets(c_name, char_length - 1, stdin);
        clear_n(c_name);
        clearScreen();
        if (c_name[0] != '\0') {
            name = c_name;
            correct_name = check_group(name);
            if (name == "_")
                return "\0";
            else if (name == "0")
                return "0";
        }
        else correct_name = 0;
    }
    return name;
}

std::string groupnum(){
    char c_num[char_length];
    std::string num;
    bool correct = 0;
    while (!correct) {
        correct = 1;
        printf("Введите номер ученика в группе или _ для оставления строки пустой\n");
        fgets(c_num, char_length - 1, stdin);
        clear_n(c_num);
        clearScreen();
        if (c_num[0] != '\0') {
            num = c_num;
            if (check_ref(num[0], '_') && num.length() == 1) {
                return "";
            }
            if (check_ref(num[0], '-')) {
                printf("Число должно быть положительным\n");
                correct = 0;
                continue;
            }
            for (int i = 0; i < num.length(); i++) {
                if (!check_is_int(num[i])) {
                    correct = 0;
                }
            }
            if (correct == 0) {
                printf("Вы должны ввести число\n");
            }   
        }
        else correct = 0;
    }
    return num;
}

std::string enter_password(){
    char c_pass[pass_length + 1];
    std::string pass;
    bool correct = 0;
    while (!correct) {
        bool devmod = 0; // При вводе 1-м символом пробел программа не проверяет правильность написания пароля
        correct = 0;
        printf("Введите пароль студента\n"
               "Пароль должен содержать не менее 8 символов и не более 20 символов\n"
               "Пароль должен содержать хотя бы одну букву, заглавную букву, "
               "цифру и специальный знак\n"
               "Введите 0 для возврата в меню\n");
        if (fgets(c_pass, pass_length + 1, stdin) == NULL) {
            printf("Ошибка ввода\n");
            continue;
        }
                clear_n(c_pass);             
        pass = c_pass;
        if (pass[0] == ' ') {    // "Аварийный режим" ввод любой строки
            devmod = 1;
            for (int i = 1; i <= pass.length(); i++){
                pass[i-1] = pass[i];
            }
            printf("Вы ввели пароль %s выхотите продолжить?\n"
                   "[Y/N]\n",
                   pass.c_str());
            correct = yorn();
            if(correct){
                clearScreen();
                return pass;
                break;
            } else {
                clearScreen();
                continue;
            }
        }
        if (pass == "0"){
            clearScreen();
            printf("Возврат в главное меню");
            return "0";
        }
        if (pass.length() <= 8) {
            //clearScreen();
            printf ("\033[1;31m%s Пароль должен содержать не менее 8 символов\033[0m\n", pass.c_str());
            continue;
        } else if (pass.length() == pass_length) {
            printf("\033[1;31m%s Пароль должен содержать не более 20 "
                   "символов\033[0m\n",
                   pass.c_str());
            while(getchar() != '\n');
            continue;
        }
        struct Password_check {
            bool capital = 0;
            bool general = 0;
            bool integer = 0;
            bool special = 0;
        };
        struct Password_check pc;
        for (int i = 0; i < pass.length(); i++) {
            if (check_first_char(pass[i]))
                pc.capital = 1;
            else if (check_char(pass[i]))
                pc.general = 1;
            else if (check_is_int(pass[i]))
                pc.integer = 1;
            else if (std::ispunct(pass[i]))
                pc.special = 1;
            else {
                clearScreen();
                printf("\033[1;31mКакая-то ошбика(\n"
                       "Пароль %s"
                       "пробелема с символом %d символ %c\n"
                       "Введите правильный пароль\033[0m\n",
                       pass.c_str(), i, pass[i]);
                continue;
            }
        }
        if(pc.capital && pc.general && pc.integer && pc.special){
            correct = 1;
        } else {
            //clearScreen();
            printf("\033[1;31m%s\n", pass.c_str());
            correct = 0;
            if (pc.capital == false)
                printf("Пароль должен содержать заглавные буквы\n");
            if (pc.general == false)
                printf("Пароль должен содержать буквы\n");
            if (pc.integer == false)
                printf("Пароль должен содержать цифру\n");
            if (pc.special == false)
                printf("Пароль должен содержать специальный знак\n");
            if (!(pc.capital || pc.general || pc.special || pc.integer))
                printf("Чумба проверь клавиатуру, возможно ты пишешь не на "
                       "английском\n");
            printf("\033[0m");
        }
    }
    return pass;
}

void instruction() {
    const size_t width = char_length;
    char line[256];

    FILE* file = fopen("instruction.md", "r");
    if (!file) {
        printf("Ошибка: файл instruction.md не найден!\n");
        _getch();
        return;
    }

    while (fgets(line, width, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);

    printf("\nНажмите любую клавишу для возврата в меню...\n");
    _getch();
    clearScreen();
}