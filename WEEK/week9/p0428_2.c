#include <stdio.h>

int main() {
    int MA[10][10], i, j, value=0;
    int* ppp = &MA[0][0];
    for(i=0; i<10; i++)
        for (j=0; j<10; j++)
            *(ppp + 10*i + j) = (value++);
    for(i=0; i<10; i++) {
        for (j=0; j<10; j++) {
            printf("%d ", *(ppp + 10*i + j));
        }
        printf("\n");
    }
    return 0;
}
