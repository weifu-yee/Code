#include <stdio.h>
#include <stdlib.h>

int main(){
    int x,y;
    char pr;
    scanf("%d %d",&x,&y);
    if (x>0&&y>0){pr='1';}
    else if (x<0&&y>0){pr='2';}
    else if (x<0&&y<0){pr='3';}
    else if (x>0&&y<0){pr='4';}
    else if (!x&&y){pr='y';}
    else if (!y&&x){pr='x';}
    else if (!x&&!y){pr='o';}

    printf("%c",pr);
    return 0;
}
