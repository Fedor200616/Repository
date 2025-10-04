#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string>

//Проверь комментарии

void choose_enter_type();
void name();

int main() {
    name();  
    ;;choose_enter_type();
    return 0;
}

void choose_enter_type() {
    int enter_num;
    printf("Выберите тип ввода: \n"
      "1) Ввод Фамилии студента; \n"
      "2) Ввод пароля студента; \n"
      "3) Закрыть программу.\n");    //В будущем сделать проверку ошибок
    enter_num = 1;
    //enter_num = getchar();
    switch (enter_num) {
    case 1:
      puts("Вызов функции Name");
      name();      
      break;      
    case 2:
      puts("Вызов функции Password");
      break;      
    case 3:
      puts("Вызов функции Endprogramm");
      break;
    }
    
    printf("%i", enter_num);
}

void name() {
  bool k = 0; // Значение правильности ввода фамилии
  char* secname = "Porno58";
  //char* secname = new char[255];
  std::string s_secname;  
    while (k == 0) {
      printf("Введите фамилию студента или 0 для выхода в меню \n");
      // if (fgets(secname, 255, stdin) != NULL) {
      //secname = "Porno58";
      if(secname != NULL){
        puts(secname);
        k = 1;        
      }
      else{
          choose_enter_type();//Вообще нужно проверять на возможные ошибки
      }      
    }
}
