#include <stdio.h>
#include <stdlib.h>

int main(){
    int p1,b1,s1,s2;
    scanf("%d%d%d%d",&p1,&b1,&s1,&s2);
    if(!p1){
            printf("1");}
    else{
        if(b1 && s1>30&&s1<70 ){ printf("2");}
        else if(!b1 && s1<=50 && s2>=60 ){printf("3");}
        else{ printf("4"); }
    }
    return 0;


}

