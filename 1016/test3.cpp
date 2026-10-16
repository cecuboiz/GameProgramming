#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// ¬¥?¬â¬ã¬Ú¬Û¬Ô ¬Ù¬å¬â¬Ñ¬ç ¬æ¬å¬ß¬Ü¬è (¬´ ¬ç¬ï¬Ý¬Ò¬ï¬â ¬Ò¬à¬Ý¬à¬ß ¬ä??¬ß¬Ú¬Û ¬ï¬â¬Ô¬ï¬Ý¬ä¬Ú¬Û¬ß ¬ä?¬Ý?¬Ó??¬Õ)
void draw_shape(int x, int y, int rotation) {
    gotoxy(x, y);
    
    if (rotation == 0) { // ¬¥¬ï¬ï¬ê ¬ç¬Ñ¬â¬ã¬Ñ¬ß ¬´
        gotoxy(x, y);     printf("  #  \n");
        gotoxy(x, y + 1); printf("###\n");
    } 
    else if (rotation == 1) { // ¬¢¬Ñ¬â¬å¬å¬ß ¬ä¬Ú¬Û¬ê ¬ï¬â¬Ô¬ï¬ã¬ï¬ß
        gotoxy(x, y);     printf("#  \n");
        gotoxy(x, y + 1); printf("## \n");
        gotoxy(x, y + 2); printf("#  \n");
    } 
    else if (rotation == 2) { // ¬¥¬à¬à¬ê ¬ç¬Ñ¬â¬ã¬Ñ¬ß
        gotoxy(x, y);     printf("###\n");
        gotoxy(x, y + 1); printf("  #  \n");
    } 
    else if (rotation == 3) { // ¬©??¬ß ¬ä¬Ú¬Û¬ê ¬ï¬â¬Ô¬ï¬ã¬ï¬ß
        gotoxy(x, y);     printf("  #\n");
        gotoxy(x, y + 1); printf("##\n");
        gotoxy(x, y + 2); printf("  #\n");
    }
}

int main(void) {
    int x = 10, y = 5; // ¬¥?¬â¬ã¬Ú¬Û¬ß ¬ï¬ç¬Ý¬ï¬ç ¬Ü¬à¬à¬â¬Õ¬Ú¬ß¬Ñ¬ä
    int rotation = 0;  // ¬¿¬â¬Ô¬ï¬Ý¬ä¬Ú¬Û¬ß ¬ä?¬Ý?¬Ó (0, 1, 2, 3)
    char key;

    system("cls"); // ¬¥¬ï¬Ý¬Ô¬ï¬è ¬è¬ï¬Ó¬ï¬â¬Ý¬ï¬ç

    while (1) {
        system("cls"); // ¬¥¬ï¬Ý¬Ô¬ï¬è¬ï¬ï ¬è¬ï¬Ó¬ï¬â¬Ý¬ï¬ï¬Õ ¬ê¬Ú¬ß¬ï ¬Ò¬Ñ¬Û¬â¬Ý¬Ñ¬Ý¬Õ ¬Ù¬å¬â¬ß¬Ñ
        
        printf("=== T-Shape Movement & Rotation Program ===\n");
        printf("Use Arrow Keys to Move | Space to Rotate | ESC to Exit\n\n");
        
        draw_shape(x, y, rotation);

        if (_kbhit()) {
            key = _getch();
            
            if (key == 224) { // ¬³¬å¬Þ¬ä¬Ñ¬Û ¬ä¬à¬Ó¬é¬Ý¬å¬å¬â¬å¬å¬Õ
                key = _getch();
                switch (key) {
                    case 72: y--; break; // ¬¥¬ï¬ï¬ê
                    case 80: y++; break; // ¬¥¬à¬à¬ê
                    case 75: x--; break; // ¬©??¬ß
                    case 77: x++; break; // ¬¢¬Ñ¬â¬å¬å¬ß
                }
            } 
            else if (key == 32) { // Space ¬ä¬à¬Ó¬é (¬¿¬â¬Ô??¬Ý¬ï¬ç)
                rotation = (rotation + 1) % 4;
            } 
            else if (key == 27) { // ESC ¬ä¬à¬Ó¬é (¬¤¬Ñ¬â¬Ñ¬ç)
                break;
            }
        }
        Sleep(50);
    }

    return 0;
}
