#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// === Цвета терминала ===
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define CLEAR   "\033[H\033[J"

// === Пункты меню ===
const char *menu_items[] = {
    "NEW GAME",
    "OPTIONS",
    "LOAD GAME",
    "SAVE GAME",
    "QUIT GAME"
};

#define MENU_SIZE (sizeof(menu_items)/sizeof(menu_items[0]))

// === Рисуем ASCII логотип DOOM ===
void draw_logo() {
    printf(YELLOW);
    printf("============================================================\n");
    printf("       ██████╗  ██████╗  ██████╗ ███╗   ███╗\n");
    printf("       ██╔══██╗██╔═══██╗██╔═══██╗████╗ ████║\n");
    printf("       ██████╔╝██║   ██║██║   ██║██╔████╔██║\n");
    printf("       ██╔══██╗██║   ██║██║   ██║██║╚██╔╝██║\n");
    printf("       ██████║╚ ██████╔╝╚██████╔╝██║ ╚═╝ ██║\n");
    printf("       ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝     ╚═╝\n");
    printf("============================================================\n");
    printf(RESET);
}

// === Рисуем меню ===
void draw_menu(int selected) {
    for (int i = 0; i < MENU_SIZE; i++) {
        if (i == selected)
            printf(RED " > %s <\n" RESET, menu_items[i]);
        else
            printf("   %s\n", menu_items[i]);
    }
}

// === Главная функция ===
int main() {
    int selected = 0;
    char input;

    system("clear");
    draw_logo();
    draw_menu(selected);

    printf("\nUse [W/S] to move, [ENTER] to select.\n");

    while (1) {
        input = getchar();

        if (input == 'w' || input == 'W') {
            selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
        } else if (input == 's' || input == 'S') {
            selected = (selected + 1) % MENU_SIZE;
        } else if (input == '\n') {
            system("clear");
            draw_logo();
            printf(RED "\nYou selected: %s\n\n" RESET, menu_items[selected]);
            if (selected == MENU_SIZE - 1) {
                printf("Exiting DOOM... Goodbye, marine!\n");
                break;
            } else {
                printf("Pretending to load %s...\n", menu_items[selected]);
                sleep(1);
            }
            printf("\nPress ENTER to go back to menu.\n");
            getchar(); // ждем ENTER
        }

        system("clear");
        draw_logo();
        draw_menu(selected);
        printf("\nUse [W/S] to move, [ENTER] to select.\n");
    }

    return 0;
}
