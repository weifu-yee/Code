#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void setup_win(int* my_win, int key) {
    int i,j;
    for (i=0;i<10;i++) {
        for (j=0;j<10;j++){
            *(my_win+i*10+j)=i*10+j+key;
}	}	}
void draw_win(int* my_win) {
    int i,j;
    for (i=0;i<10;i++) {
        for (j=0;j<10;j++){
            printf("%d ", *(my_win+i*10+j));
        }
        printf("\n");
    }
}
void gotoxy(int col, int row) {
	HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD position = { col, row };
	SetConsoleCursorPosition (h, position);
}	

int main(){
    int my_win[10][10] = {0};
    draw_win(my_win);
    setup_win(my_win, 1);
    gotoxy(5,5);
    draw_win(my_win);
    setup_win(my_win, 2);
    draw_win(my_win);
}