#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "Laba.h"
//#include "function.h"
//#include "utility.h"
//#include "settings.h"

struct Settings{
    int AutoCapLetter;
    char AutoCreateFile[char_length];
};
struct Settings s;

void settingscheck() {
    FILE *file = fopen("config.cfg", "r");
    if (file == NULL){
        file = fopen("config.cfg", "w");
        if (file == NULL){
            printf("Не удается создать файл настроек");
            return;          
        }
    fprintf(file, "AutoCapLetter = 0\n");
    fprintf(file, "AutoCreateFile = text.txt\n");
    fclose(file);
    return;
    }

    char line[256], key[128], value[128];
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, " %127[^=]= %127[^\n]", key, value) == 2) {
            char *k = key;
            while (*k == ' ' || *k == '\t')
              k++;
            char *v = value;
            while (*v == ' ' || *v == '\t')
                v++;

            for (int i = strlen(k) - 1; i >= 0 && (k[i] == ' ' || k[i] == '\t'); i--)
                k[i] = 0;
            for (int i = strlen(v) - 1; i >= 0 && (v[i] == ' ' || v[i] == '\t'); i--)
                v[i] = 0;
            // Проверка настроек
            if (strcmp(k, "AutoCapLetter") == 0)
                s.AutoCapLetter = atoi(v);
            else if (strcmp(k, "AutoCreateFile") == 0)
                strncpy(s.AutoCreateFile, v, sizeof(s.AutoCreateFile) - 1);
        }
    }
    fclose (file);
}

void saveSettings(){
    FILE *file = fopen("config.cfg", "w");
    if (!file) {
        printf("Ошибка, не удалось сохранить настройки");
        return;
    }
    fprintf(file, "AutoCapLetter = %d\n", s.AutoCapLetter);
    fprintf(file, "AutoCreateFile = %s\n", s.AutoCreateFile);
    fclose(file);
}

void settingsmenu() {
    // clearScreen();
    int num = 0;
    printf ("Выберите номер настройки\n");
    printf("1) AutoCapLetter = %d / Автозамена первой буквы фамилии\n",
           s.AutoCapLetter);
    printf("2) AutoCreateFile = %s / Автоматическое создание файла\n",
           s.AutoCreateFile);
    scanf("%i", &num);
    while (getchar() != '\n');
    switch (num) {
    case 1:
        // clearScreen();
        printf("1) AutoCapLetter = %d / Автозамена первой буквы фамилии\n",
               s.AutoCapLetter);
        printf("Введите новое значение\n");
        
    }
}

int main() {
    settingscheck();
    //settingsmenu();
    s.AutoCapLetter = 1;
    saveSettings();
    //settingsmenu();
}
