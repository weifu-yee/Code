#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int do_max();
int do_min();

int main()
{
    int row,k,a,times=0,summing = 0;
    char string1[300];
    const char*sum = "sum";
    const char*max = "max";
    const char*min = "min";

    scanf("%d",&row);
    for (int i=0;i<row;i++){
        scanf("%s",string1);
        if (!strcmp(string1, sum)){
            scanf("%d",&k);
            for(int j=0;j<k;j++){
                scanf("%d",&a);
                summing += a;
            }
            times += k;
        }
        if (!strcmp(string1, max)){
            summing += do_max();
            times ++;
        }
        if (!strcmp(string1, min)){
            summing += do_min();
            times ++;
        }
    }

    printf("%d %d",summing,times);
    return 0;
}

int do_max(){
    int a[3] = {0},big = 0;
    for(int i=0;i<3;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<3;i++){
        if(a[i] > big)
            big = a[i];
    }
    return big;
}

int do_min(){
    int a[3] = {0},small = 0;
    for(int i=0;i<3;i++){
        scanf("%d",&a[i]);
    }
    small = a[0];
    for(int i=1;i<3;i++){
        if(a[i] < small)
            small = a[i];
    }
    return small;
}

