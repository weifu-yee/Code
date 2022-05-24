#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
//#include "conio.h"

#define SIZE 10

typedef struct {
    int x;
    int y;
} Point;

Point pt(int, int);
int visit( Point, Point);
void print();
void show();
int maze[SIZE][SIZE];

int main(void) {
	int i,j;
	FILE *inf;

	inf = fopen("D:/Code/WEEK/week15/input.txt","r");
	while (feof(inf)==0) {
		for (i=0;i<SIZE;i++)
			for (j=0;j<SIZE;j++)
				fscanf(inf,"%d", &maze[i][j]);
	}
	if(!visit(pt(1, 1), pt(8, 8))) {
        printf("\n�S�����X�f�I\n");
    }
//    print();

	system("pause");
    return 0;
}

Point pt(int x, int y) {
    Point p = {x, y};
    return p;
}

int visit(Point start, Point end) {
	char c;

    // if (kbhit()) {
    //         c = getch();
	// 	    printf("User input %c\n", c);
	// 		Sleep(10);
	// }

	show();
	if(!maze[start.x][start.y]) {
         maze[start.x][start.y] = 1;
         if(!maze[end.x][end.y] &&
            !(visit(pt(start.x, start.y + 1), end) ||
              visit(pt(start.x + 1, start.y), end) ||
              visit(pt(start.x, start.y - 1), end) ||
              visit(pt(start.x - 1, start.y), end))) {
                 maze[start.x][start.y] = 0;
         }
    }
	show();
    return maze[end.x][end.y];

}

void show() {
	int i, j;

	system("CLS");
	for(i=0; i<SIZE; i++) {
		for (j=0; j<SIZE; j++) {
				switch(maze[i][j]) {
					case 0 : printf(" "); break;
					case 1 : printf("o"); break;
					case 2 : printf("X");
				}
		}
		printf("\n");
	}
	Sleep(100);
	return;
}

void print() {
    int i, j;
    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++)
			switch(maze[i][j]) {
				case 0 : printf("  "); Sleep(100); break;
				case 1 : printf("��"); Sleep(100); break;
				case 2 : printf("�i");
			}
        printf("\n");
    }
}

