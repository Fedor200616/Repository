#define _CRT_SECURE_NO_WARNINGS
#include "Laba.h"
#include "function.h"
#include "utility.h"

FILE* makefile() {     //Основная функция для работы с файлом с фамилиями
    clearScreen();
    char c_filename[char_length];
    std::string filename;    
    bool check_true = 0;
    std::string path = "myfiles";
    
	while (check_true == 0) {    // Создаем папку myfiles, если ее нет, выводим файлы с расширением .txt в ней
        if (!std::filesystem::exists(path)) {
            try {
                if (std::filesystem::create_directory(path)) {
                    std::cout << "Папка 'myfiles' успешно создана!\n" << std::endl;
                }
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::cout << "Ошибка создания папки: \n" << e.what() << std::endl;
                return nullptr;
            }
        }
		printf("Доступные файлы:\n"); // Выводим в cmd файлы с расширением .txt

		for (const auto& entry : std::filesystem::directory_iterator(path)) { //Перебираем файлы в папке и выводим только .txt
            if (entry.path().extension() == ".txt") {
                printf("%s \n", entry.path().filename().string().c_str());
            }
        }
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
	
	FILE* file = fopen((path + "/" + filename).c_str(), "a+"); // Открываем файл на дозапись и чтение

    if (!file){
        printf("\033[1;31mОшибка открытия файла!\n\033[0m");
        
        return nullptr;
    } else {
        printf("Файл %s успешно открыт!\n", filename.c_str());
        return file;
    }    
}

void secname() {   // Функция работы с файлом фамилий
    printf("Выберите файл с фамилиями\n");
    FILE *file = makefile();
    if (!file){
        printf("\033[1;31mОшибка открытия файла!\033[0m\n");
        //menu();
        return;
    }
	struct Secname_struct { // Структура для хранения временных данных
        std::string buffer_secname;
        std::string buffer_group;
        std::string buffer_num;
    };
    struct Secname_struct sn;
    
	bool file_exit = 0; // Флаг выхода из функции
    while (!file_exit) {
        bool itsall = 0; // Флаг полного ввода данных
        while (!itsall) {
            sn.buffer_secname = name(); // Ввод фамилии
            if (sn.buffer_secname == "0") { // Проверка на выход в меню
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
            while (!itsall) { // Ввод группы
                sn.buffer_group = group();
                clearScreen();
                if (sn.buffer_group == "0") {
                    printf("Возврат к выбору фамилии\n");
                    break;
                }
                printf("Номер группы %s \n", sn.buffer_group.c_str());
                while (!itsall) { // Ввод номера ученика в группе
                    sn.buffer_num = groupnum();
                    clearScreen();
                    if (sn.buffer_num == "0") {
                        printf("Возврат к выбору группы\n");
                        break;
                    }
                    else itsall = 1;
                }
            }
        }
        printf("Записать данные студента\n"
            "| %-20s | %-12s | %-5s|\n"
            "Выберите Y или Enter для записи\n"
            "Выберите N для отмены\n"
            "Выберите S для выхода в меню с сохранением или\n"
            "Выберите R для возврата без сохранения данных\n"
            "[Y/N/S/R]\n",
            sn.buffer_secname.c_str(), sn.buffer_group.c_str(), sn.buffer_num.c_str()); // Вывод введенных данных
        int k = ynrs(); // Ввод ответа пользователя
        clearScreen();
        if (k == 1 || k == 3) { // Запись данных в файл
            fprintf(file, "| %-20s | %-12s | %-5s |\n", sn.buffer_secname.c_str(),
                sn.buffer_group.c_str(), sn.buffer_num.c_str());
            printf("Данные успешно записаны!\n");
        }
        if (k == 2 || k == 3) { // Выход из функции
            file_exit = 1;
            fprintf(file, "\n");
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
    }
}

void password() {  // Функция работы с файлом паролей
    printf("Выберите файл паролей\n");
	FILE* file = makefile(); // Вызываем функцию создания и открытия файла
    if (!file){ 
        printf("\033[1;31mОшибка открытия файла!\n\033[0m");
        //menu();
        return;
    }
	struct Password_struct { // Структура для хранения временных данных
        std::string buffer_password;
        std::string buffer_group;
        std::string buffer_num;
    };
    struct Password_struct pw; 
	int file_exit = 0; // Флаг выхода из функции
    while (!file_exit) {
        bool itsall = 0; // Флаг полного ввода данных
        while (!itsall) { // Ввод пароля
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
            while (!itsall) {    // Ввод группы
                pw.buffer_group = group();
                clearScreen();
                if (pw.buffer_group == "0") {
                    printf("Возврат к выбору пароля\n");
                    break;
                }
                printf("Номер группы %s \n", pw.buffer_group.c_str());
                while (!itsall) {    // Ввод номера ученика в группе
                    pw.buffer_num = groupnum();
                    clearScreen();
                    if (pw.buffer_num == "0") {
                        printf("Возврат к выбору группы\n");
                        break;
                    }
                    else itsall = 1;
                }
            }
        }
        printf("Записать данные студента\n"
            "| %-20s | %-12s | %-5s|\n"
            "Выберите Y или Enter для записи\n"
            "Выберите N для отмены\n"
            "Выберите S для выхода в меню с сохранением или\n"
            "Выберите R для возврата без сохранения данных\n"
            "[Y/N/S/R]\n",
            pw.buffer_password.c_str(), pw.buffer_group.c_str(), pw.buffer_num.c_str());     // Вывод введенных данных
        int k = ynrs(); // Ввод ответа пользователя
        clearScreen();
        if (k == 1 || k == 3) { // Запись данных в файл
            fprintf(file, "| %-20s | %-12s | %-5s |\n", pw.buffer_password.c_str(),
                pw.buffer_group.c_str(), pw.buffer_num.c_str());
            printf("Данные успешно записаны!\n");;
        }
        else if (k == 2) { // Выход из функции
            file_exit = 1;
            fprintf(file, "\n");
            clearScreen();
            fclose(file);
            //menu();
            return;
        }
    }
}

int menu() {  // Главное меню
    clearScreen();
	bool wrong_enter = 0; // Флаг неверного ввода
	bool k = 0; // Флаг выхода из меню
	char enter_num; // Ввод номера меню
    while (!k) {
        printf("Выберите тип ввода: \n"
               "1) Ввод фамилии студента; \n"
               "2) Ввод пароля студента;\n"
               "3) Инструкция пользователю;\n"
               "0) Закрыть программу.\n");
             
        enter_num = _getch();
        printf("\n");
        clearScreen();
        switch (enter_num) {
        case '1':     //Вызов функции Name
            secname();
            k = 1;            
            break;
		case '2':   // Вызов функции Password
            password();
            k = 1;
            break;
		case '3': // Вызов функции Instruction
            instruction();
            break;
		case '0': // Выход из программы
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

std::string name() { // Ввод фамилии
	bool k = 0; // Флаг правильного ввода
	char c_secname[255]; // Временный массив для ввода фамилии
	std::string b_secname; // Временная строка для проверки заглавной буквы
	std::string secname; // Строка для фамилии
    clearScreen();
    while (!k) {
        printf("Введите фамилию студента или 0 для выхода в меню \n");
        c_secname[0] = '\0';
		fgets(c_secname, char_length - 1, stdin); // Ввод фамилии
		clear_n(c_secname);  // Убираем \n из строки
        clearScreen();
		if (c_secname[0] != '\0') { // Проверка на пустой ввод
            secname = c_secname; 
            k = 1;
			for (int i = 0; i < secname.length(); i++) { // Проверка на правильность ввода
				if (check_ref(secname[0], '0') && secname.length() == 1) { // Выход в меню на 0
                    k = 1;
                    return "0";
                    break;
                }                    
                else if (k == 1 && (i != 0 && !((check_char(secname[i]) || RU_check_char(secname[i]) || check_ref(secname[i], '-') || check_ref(secname[i], '_') || check_ref(secname[i], '\''))))) {
                    printf("Допустимы только маленькие буквы и знаки -, _, ' \n");
                    k = 0;
				} // Проверка на допустимые символы в фамилии
            }
			if (!k) { // При ошибки ввода
                printf("\033[1;31m%s\033[0m\n"
                       "Вы уверены в правильности ввода?\n"
                       "[Y/N]\n", secname.c_str());
                k = yorn();
                clearScreen();
            }
			if (!(check_first_char(secname[0]) || RU_check_first_char(secname[0]) && k == 1)) { // Проверка на заглавную букву
                printf("Фамилия должна начинаться на заглавную букву,\n");
				if (check_char(secname[0])) { // Замена латинской буквы на заглавную
                    b_secname = secname;
                    b_secname[0] -= Aa;
                    printf("Вы имели ввиду %s?\n"
                           "[Y/N]\n",
                           b_secname.c_str());
                    k = yorn();
                    if (k) {
                        secname = b_secname;
                    }
                }
				else if (RU_check_char(secname[0])) { // Замена русской буквы на заглавную
                    b_secname = secname;
                    b_secname[0] -= Aa;
                    printf("Вы имели ввиду %s?\n"
                        "[Y/N]\n",
                        b_secname.c_str());
                    k = yorn();
                    if (k) {
                        secname = b_secname;
                    }
				}
                else k = 0;
            }
        }            
		else { // Если пользователь ввел пустую строку
            clearScreen();
            k = 0;
        }
    }
    return secname;
}



std::string group() { // Ввод группы
	char c_name[char_length]; // Временный массив для ввода группы
	bool correct_name = 0; // Флаг правильного ввода
	std::string name; // Строка для группы
    while (!correct_name) {
        printf("Введите номер группы формата M7O-206BV-24 \n"
               "Вы можете ввести _ для оставления строки пустой или 0 для возврата назад\n");
        fgets(c_name, char_length - 1, stdin); 
        clear_n(c_name);
        clearScreen();
		if (c_name[0] != '\0') { // Проверка на пустой ввод
            name = c_name;
			correct_name = check_group(name); // Проверка на правильность ввода
			if (name == "_") // Возврат пустой строки
                return "\0";
            else if (name == "0")
                return "0";
        }
		else correct_name = 0; // При пустом вводе
    }
    return name;
}

std::string groupnum() { // Ввод номера ученика в группе
	char c_num[char_length]; // Временный массив для ввода номера ученика в группе
	std::string num; // Строка для номера ученика в группе
	bool correct = 0; // Флаг правильного ввода
    while (!correct) {
        correct = 1;
        printf("Введите номер ученика в группе или _ для оставления строки пустой\n");
        fgets(c_num, char_length - 1, stdin);
        clear_n(c_num);
        clearScreen();
		if (c_num[0] != '\0') { // Проверка на пустой ввод
            num = c_num;
			if (check_ref(num[0], '0') && num.length() == 1) { // Выход в меню на 0
                return "0";
            }
			if (check_ref(num[0], '_') && num.length() == 1) { // Возврат пустой строки
                return "";
            }
			if (check_ref(num[0], '-')) { // Проверка на отрицательное число
                printf("Число должно быть положительным\n"); 
                correct = 0;
                continue;
            }
			for (int i = 0; i < num.length(); i++) { // Проверка на правильность ввода
                if (!check_is_int(num[i])) {
                    correct = 0;
                }
            }
			if (correct == 0) { // При ошибке ввода
                printf("Вы должны ввести число\n");
            }   
        }
		else correct = 0; // При пустом вводе
    }
    return num;
}

std::string enter_password() { // Ввод пароля
	char c_pass[char_length]; // Временный массив для ввода пароля
	std::string pass; // Строка для пароля
	bool correct = 0; //Флаг правильного ввода
    while (!correct) {
        bool devmod = 0; // При вводе 1-м символом пробел программа не проверяет правильность написания пароля
        correct = 0;
        printf("Введите пароль студента\n"
               "Пароль должен содержать не менее 8 символов и не более %d символов\n"
               "Пароль должен содержать хотя бы одну латинскую букву и латинскую заглавную букву, "
               "цифру и специальный знак\n"
               "Введите 0 для возврата в меню\n", pass_length); 
        if (fgets(c_pass, pass_length + 1, stdin) == NULL) {
            printf("Ошибка ввода\n");
            continue;
        }
        clear_n(c_pass);             
        pass = c_pass;
        clearScreen();
        if (pass[0] == ' ') {    // "Аварийный режим" ввод любой строки
            devmod = 1;
            for (int i = 1; i <= pass.length(); i++){
                pass[i-1] = pass[i];
            }
            printf("Вы ввели пароль %s вы хотите продолжить?\n"
                   "[Y/N]\n",
				pass.c_str()); //Уточняем у пользователя правильность ввода
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
		if (pass == "0") { // Выход в меню на 0
            clearScreen();
            printf("Возврат в главное меню");
            return "0";
        }
		if (pass.length() < 8) { // Проверка на минимальную длину пароля
            //clearScreen();
            printf ("\033[1;31m%s Пароль должен содержать не менее 8 символов\033[0m\n", pass.c_str());
            continue;
		}
		else if (pass.length() == pass_length) { // Проверка на максимальную длину пароля
            printf("\033[1;31m%s Пароль должен содержать не более %d "
                   "символов\033[0m\n",
                   pass.c_str(), pass_length);
            while(getchar() != '\n');
            continue;
        }
		struct Password_check { // Структура для проверки правильности ввода пароля
            bool capital = 0;
            bool general = 0;
            bool integer = 0;
            bool special = 0;
			bool RU = 0;
        };
        struct Password_check pc;
		for (int i = 0; i < pass.length(); i++) { // Проверка на правильность ввода пароля
			if (check_first_char(pass[i])) // Проверка на заглавную букву
                pc.capital = 1;
			else if (check_char(pass[i])) // Проверка на маленькую букву
                pc.general = 1;
			else if (check_is_int(pass[i])) // Проверка на цифру
                pc.integer = 1;
			else if (std::ispunct(pass[i])) // Проверка на специальный знак
                pc.special = 1;
			else if (RU_check_char(pass[i]) || RU_check_first_char(pass[i])) { // Проверка на отсутсвие русских букв
                clearScreen();
                pc.RU = 1;
                printf("\033[1;31mПароль не должен содержать русские буквы\n\033[0m",
                    pass.c_str(), i, pass[i]);
                break; break;
            }
			else { // При недопустимом символе
                clearScreen();
                printf("\033[1;31mКакая-то ошбика(\n"
                       "Пароль %s\n"
                       "Пробелема с символом %d символ %c\n"
                       "Введите правильный пароль\033[0m\n",
                       pass.c_str(), i, pass[i]);
                break;
            }
        }
		if (pc.RU) { // При наличии русских букв в пароле
			continue;
		}
		if (pc.capital && pc.general && pc.integer && pc.special) { // Если все условия выполнены
            correct = 1;
		}
		else { // Если условия не выполнены
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
                printf("Проверьте ввод, какая-то проблема с вводом\n");
            printf("\033[0m");
        }
    }
    return pass;
}

void instruction() { // Функция инструкции пользователю
	const size_t width = char_length; // Ширина строки
	char line[256]; // Временный массив для строки

	FILE* file = fopen("instruction.md", "r"); // Открытие файла инструкции
    if (!file) {
        printf("Ошибка: файл instruction.md не найден!\n");
        printf("Нажмите любую клавишу для возврата в меню...\n");
        _getch();
        return;
    }

    while (fgets(line, width, file) != NULL) {
        printf("%s", line);
	} // Чтение и вывод строки из файла

    fclose(file);

    printf("\nНажмите любую клавишу для возврата в меню...\n");
    _getch();
    clearScreen();
}
