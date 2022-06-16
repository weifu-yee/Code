#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
    int result;
    double r01, rnd;
 
    // 亂數種子
    srand((unsigned)time(NULL));
    // 產生 [0,1) 之亂數
    r01 = (double)(rand()) / (RAND_MAX + 1.0) ;
    printf("%lf",r01);
    // 產生 [1,7) 之亂數
    rnd = r01 * (7.0 - 1.0) + 1.0;
    // 強制轉型給 result
    result = (int)(rnd);
    printf("result = %d\n", result); // 輸出結果
    getchar();
    return 0;
}