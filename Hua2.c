//陳蔚榑 110033116 PME25
#include <stdio.h>
int main(){
    int Index[1000] = {0};
    int i=1, first=1;

    for(int h=0; h<1000; h++)
        Index[h] = 1; //initialize arrays to 1 

    printf("Prime numbers are");

    while (i<1000){
        if (Index[i]){
            for (int j=i+1; j<1000; j++){
                if ( !((j+1) % (i+1)) )
                    Index[j]=0;
            }
            if (!first){
                printf(", %d",i+1);
            }else{
                printf(" %d",i+1);
                first=0;
            }
        }
        i++;
    }
    return 0;
}