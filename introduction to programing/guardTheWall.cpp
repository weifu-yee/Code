#include <iostream>
using namespace std;
typedef struct{
    int a;
    int b;
}guardRegion;

int wallNumber(int wall, int soldier){
    int maxWall = 0;
    guardRegion region[soldier];
    bool guardedWall[wall]={0};
    for(int i = 0; i < soldier; i ++){
        cin>>region[i].a>>region[i].b;
    }
    for(int i = 0; i < soldier; i ++){
        for(int j = i; j < soldier; j ++){
            for(int k = 0; k < wall; k++){
                if(k>=region[i].a && k<=region[i].b){
                    guardedWall[k] = true;
                    break;
                }
                if(k>=region[j].a && k<=region[j].b){
                    guardedWall[k] = true;
                    break;
                }
            }
        }
    }
}

int main(){
    int n;
    cin>>n;
    for(int i = 0; i < n; i++){
        int wall, soldier;
        cin>>wall>>soldier;
        cout<<wallNumber(wall,soldier)<<endl;
    }
    return;
}