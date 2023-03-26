#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        //to find out the most factor number in the range
        int l;  int r;
        scanf("%d %d",&l,&r);
        int max = 0;
        int max_number = 0;
        for(int j = l; j <= r; j++){
            int factor = 0;
            for(int k = 1; k <= j; k++){
                if(j % k == 0){
                    factor ++;
                }
            }
            if(factor > max){
                max = factor;
                max_number = j;
            }
        }
    printf("%d\n",max_number);
    }
}