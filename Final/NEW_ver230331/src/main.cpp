#include "../inc/openfile.h"
#include "../inc/struct.h"

int main(){
    if(openfile() != NULL){
        printf("The file is opened!\n");
    }
    return 0;
}