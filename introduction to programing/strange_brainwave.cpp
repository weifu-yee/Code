#include<stdio.h>

int main(){
    int n;
    int answer[2000];

    scanf("%d",&n);
    for(int i = 0; i < n ;i ++){
        int axor = 0; 
        int a, b;
        scanf("%d%d",&a,&b);
        for(int j = 1; j < a; j ++){
            axor ^= j;
        }

        if(axor == b){
            answer[i] = a;
            continue;
        }

        int c = axor ^ b;
        if(c == a){
            answer[i] = a + 2;
            continue;
        }
        answer[i] = a + 1;
    }

    for(int i = 0; i < n; i ++){
        printf("%d\n",answer[i]);
    }
    return 0;
}
// int lastmain(){
//     int n;
//     int answer[2000];
//     int axor = 0;

//     scanf("%d",&n);
//     for(int i = 0; i < n ;i ++){
//         axor = 0; 
//         int a, b;
//         scanf("%d%d",&a,&b);
//         for(int j = 1; j < a; j ++){
//             axor ^= j;
//         }

//         if(axor == b){
//             answer[i] = a;
//             continue;
//         }

//         if(a == 1 && b == 1){
//             // printf("\nA1\n");
//             answer[i] = 3;
//             continue;
//         }

//         if(a == 2 && b == 2){
//             // printf("\nA2\n");
//             answer[i] = 3;
//             continue;
//         }

//         int count = 0,aa = a;
//         while (aa > 0) {
//             if (aa & 1) {  // check if the rightmost bit is 1
//                 count++;
//             }
//             aa >>= 1;  // shift the bits to the right by 1
//         }
//         if(count == 1 && a == b){
//             // printf("\nB\n");
//             answer[i] = a + 2;
//             continue;
//         }

//         count = 1;
//         aa = a;
//         while (aa > 0) {
//             if (!(aa & 1)) {  // check if the rightmost bit is 1
//                 count = 0;
//             }
//             aa >>= 1;  // shift the bits to the right by 1
//         }
//         if(count == 1 && b == 0){
//             // printf("\nC\n");
//             answer[i] = a + 2;
//             continue;
//         }

//         answer[i] = a + 1;
//     }

//     for(int i = 0; i < n; i ++){
//         printf("%d\n",answer[i]);
//     }
//     return 0;
// }