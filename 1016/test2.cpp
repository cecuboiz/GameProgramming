#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void draw_horizontal_slide(int x, int y, int length, char *s);
void draw_vertical_slide(int x, int y, int length, char *s);
void draw_rectangle(int c, int r);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);
void gotoxy(int x, int y);

void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// ¬·?¬â¬ï¬ï ¬Ù¬å¬â¬Ñ¬ç ¬æ¬å¬ß¬Ü¬è
void draw_rectangle(int c, int r) {
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];
    for(i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);
    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[4]);

    for(i = 0; i < r; i++) {
        printf("%c%c", a, b[2]);
        for(j = 0; j < c; j++)
            printf("  ");
        printf("%c%c\n", a, b[2]);
    }
    printf("%c%c", a, b[6]);
    for(i = 0; i < c; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[5]);
}

// ¬¢¬à¬ã¬à¬à ¬ã¬Ý¬Ñ¬Û¬Õ ¬Ù¬å¬â¬Ñ¬ç ¬æ¬å¬ß¬Ü¬è
void draw_vertical_slide(int x, int y, int length, char *s) {
    gotoxy(x, 1);
    draw_rectangle(1, length);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(x + 6, length + 1);
    printf("%2d", y);
}

// ¬·¬ï¬Ó¬ä¬ï¬ï ¬ã¬Ý¬Ñ¬Û¬Õ ¬Ù¬å¬â¬Ñ¬ç ¬æ¬å¬ß¬Ü¬è
void draw_horizontal_slide(int x, int y, int length, char *s) {
    int real_length = length / 2;
    gotoxy(1, y);
    draw_rectangle(real_length + 1, 1);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(real_length * 2 + 2, y - 1);
    printf("%2d", x);
}

// ¬³¬å¬Þ¬ä¬Ñ¬Û ¬ä¬à¬Ó¬é¬Ý¬å¬å¬â¬Ñ¬Ñ¬â ¬ç?¬Õ?¬Ý¬Ô?¬ç ¬æ¬å¬ß¬Ü¬è
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72: // ¬¥¬ï¬ï¬ê
            *y1 = *y1 - 1;
            if (*y1 < 1) *y1 = 1;
            break;
        case 75: // ¬©??¬ß
            *x1 = *x1 - 1;
            if (*x1 < 1) *x1 = 1;
            break;
        case 77: // ¬¢¬Ñ¬â¬å¬å¬ß
            *x1 = *x1 + 1;
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 80: // ¬¥¬à¬à¬ê
            *y1 = *y1 + 1;
            if (*y1 > y_b) *y1 = y_b;
            break;
        default:
            return;
    }
}

int main(void) {
    char *slide = "#", key;
    int x = 1, y = 1;
    int h_slide_length, v_slide_length;

    printf("Slide Bar Program\n\n");
    printf("Enter horizontal slide length (max 70): ");
    scanf("%d", &h_slide_length);
    printf("Enter vertical slide length (max 19): ");
    scanf("%d", &v_slide_length);
    system("cls");

    do {
        draw_vertical_slide(1, y, v_slide_length, slide);
        draw_horizontal_slide(v_slide_length + 3, x, h_slide_length, slide);
        key = getch();
        move_arrow_key(key, &x, &y, h_slide_length, v_slide_length);
    } while(key != 27); // ESC ¬ä¬à¬Ó¬é ¬Õ¬Ñ¬â¬Ø ¬Õ¬å¬å¬ã¬ä¬Ñ¬Ý ¬Ñ¬Ø¬Ú¬Ý¬Ý¬Ñ¬ß¬Ñ

    return 0;
}
