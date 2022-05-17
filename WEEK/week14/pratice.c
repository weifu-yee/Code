#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int stack_x[50], stack_y[50], flag, top; 
char maze[6][6];

int main(){
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    FILE *in;
    in=fopen("input.txt","r");
    for(int j=0;j<6;j++)
    {
        for(int i=0;i<6;i++)
        {
            fscanf(in,"%c",&maze[i][j]);
            while((maze[i][j]<'0')||(maze[i][j]>'2'))
            {
                fscanf(in,"%c",&maze[i][j]);
            }
        }
    }
 while(flag == 0) {
        int findapath = 0;
        for(int i = 0; i < 4; i ++){
            int nx = stack_x[top] + dx[i], ny = stack_y[top] + dy[i];
            if(nx >= 0 && nx< 6 && ny>= 0 && ny < 6){
                if(maze[nx][ny] != '0'){
                    top++;
                    stack_x[top] = nx;
                    stack_y[top] = ny;
                    if(maze[nx][ny] == '2') flag = 1;
                    maze[nx][ny] = '0';
                    findapath = 1;
                    break;
        }   }   }
        if(findapath == 0 && flag != 1) {
            if(stack_x[top] == 0 && stack_y[top] == 0)
                flag = -1;
            top--;
    }    }
    if(flag == -1)
        printf("No\n");
    else if(flag == 1){
        printf("Yes\n");
        for(int i = 0; i < top ; i++) {
            printf("(%d,%d) ", stack_x[i], stack_y[i]);
        }
        printf("(%d,%d)\n",stack_x[top], stack_y[top]);
    }
    return 0;
}
