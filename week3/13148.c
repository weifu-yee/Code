#include <stdio.h>
int main()  {
    int number , i = 2;
    int r;
    scanf("%d",&number);
    if (number == 1 )
        printf("Not");
    while(i <= number){
        r = number % i;
        if (!r && i != 2){
            printf("Not");
            break;
        }
        else if (i >= number / 2){
            printf("Prime");
            break;

        }

        i ++;

    }

    return 0;
}
