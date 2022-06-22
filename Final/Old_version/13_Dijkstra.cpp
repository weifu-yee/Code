#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~FILE~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
FILE* file(){
    FILE* inf = fopen("D:/Code/Final/INPUT file/input4.txt","r");
    if( !inf)       printf("File not found!\n"),  exit(1);
    return inf;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Structures~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
typedef struct _Vertex{
    char value;
    int x;
    int y;
    bool visited;
    struct _Connect* connect;
}_Vertex;
typedef struct _Connect{
    struct _Vertex* self;
    int face;       //describe this vertex is what direction of the vertex which belong;
    struct _Connect* next;
}_Connect;
typedef struct _Vehicle{
    _Vertex* driver;        //the driver's vertex;
    int face;       //determine the direction;
}_Vehicle;
typedef struct _Set{
    int fuel_consumption;
    struct _StepLog* step_log;
}_Set;
typedef struct _StepLog{
    _Vehicle* car;
    struct _StepLog* last;
}_StepLog;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Global Variables~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vertex* vertex[50][50];    //the map's vertex which input;
int X_width, Y_width;       //X,Y width
bool mission_spot_or_not = false;
int best_step;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function declaration~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
//run
int run(_Vehicle* start);       //run from the start;
//other
struct _Vehicle* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void make_connect_loop();     //loop to make junction
int axis_addition(int axis, int initial, int face);
void show();        //print the graph
bool check_drive(bool offset_or_not,int car_face,int* new_x,int* new_y,int dir,int ofs);
void car_offset(int* new_x,int* new_y,int car_face,int ofs);
void recursion_show(_Set** S_set, _StepLog* curr);
void update_car(bool curr_last,_Vehicle* car);
void reset_vertex();
//drive
bool forward(int* car_face,int* new_x,int* new_y);
bool backward(int* car_face,int* new_x,int* new_y);
bool rightshift(int* car_face,int* new_x,int* new_y);
bool leftshift(int* car_face,int* new_x,int* new_y);
bool turnright(int* car_face,int* new_x,int* new_y);
bool turnleft(int* car_face,int* new_x,int* new_y);
//Q S sets
void build_Q_set(_Set** Q_set, _Set** S_set, _Vehicle* start);
bool Q_set_all_NULL(_Set** Q_set);
void catch_Q( _Set** Q_set, int* _i, int* _j, int* _face);
void throw_S(_Set** Q_set, _Set** S_set, int _i, int _j, int _face);
void print_Q_S(_Set** Q_set);
void Q_update(_Set** Q_set, _Set* curr);
//S run
bool S_run(_Set** S_set);
bool mission_S_run(_Set** S_set);
void recursionUpdate_S(_Set** S_set, _StepLog* curr);


//~ ~ ~ ~ ~ ~ ~ ~ ~ ~main~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
int main(){
    _Vehicle* start = Adjacency_List();
    make_connect_loop();
    run(start);
    return 0;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~functions~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
//run
int run(_Vehicle* start){
    _Set* Q_set[Y_width][X_width][4];
    _Set* S_set[Y_width][X_width][4];
    build_Q_set(&Q_set[0][0][0], &S_set[0][0][0], start);
    print_Q_S(&Q_set[0][0][0]);    printf("\n~~~S~\n");    print_Q_S(&S_set[0][0][0]);    system("CLS");
    int gotcha = 0;
    while(Q_set_all_NULL( &Q_set[0][0][0])){
        int _i = -1, _j = -1, _face = -1;
        catch_Q( &Q_set[0][0][0], &_i, &_j, &_face);
        if( _i == -1 || _j == -1 || _face == -1){
            gotcha = -1;
            break;
        }
        throw_S( &Q_set[0][0][0], &S_set[0][0][0], _i, _j, _face);
    }
    printf("\nQ~\n");print_Q_S(&Q_set[0][0][0]);printf("S~\n");
    print_Q_S(&S_set[0][0][0]);printf("\n~~Dijkstra construction finished~~\n");
    if(gotcha == -1)       printf("gotcha = -1\n");
    system("Pause");
    char cmd = '1';
    do{
        fflush(stdin);
        reset_vertex();
        while( S_run( &S_set[0][0][0] ) );
        printf("\nPress any key not 'q' to run again!\nOr press 'q' to exit!\n");
        scanf("%c",&cmd);
    }while(cmd != 'q');
    return 0;
}
//other
struct _Vehicle* Adjacency_List(){
    FILE* inf = file();
    int i = 0;
    _Vehicle* start = (_Vehicle*) malloc( sizeof( _Vehicle));
    char _n;        //To recieve '\n' and do nothing;
    int two_or_three = 3;
    while( !feof( inf)){
        int j = 0;
        X_width = 0;
        do{
            _Vertex* new_vertex = (_Vertex*) malloc( sizeof( _Vertex));
            vertex[i][j] = new_vertex;
            new_vertex->x = j;
            new_vertex->y = i;
            new_vertex->visited = false;
            fscanf(inf,"%c",&(new_vertex->value));
            if( new_vertex->value == '3')        mission_spot_or_not = true;
            if( two_or_three && new_vertex->value == '2'){
                if( two_or_three != 2){
                    start->driver = new_vertex;
                    start->face = 1;        //defaut of lay vehicle face to right;
                }
                two_or_three --;
            }else if( two_or_three == 1){
                start->face = 0;
                two_or_three = 0;       //defaut of stand vehicle face to up;
            }
            new_vertex->connect = NULL;
            j++, X_width++;
        } while( !fscanf(inf,"%[\n]",&_n) );
        i++, Y_width++;
    }
    fclose(inf);
    return start;
}
void make_connect(int i,int j){
    int x_add[4] = {0,1,0,-1}, y_add[4] = {-1,0,1,0};
    for( int k = 3; k >= 0; k--){
        if(vertex[i][j]->value == '0')    continue;
        int new_i = axis_addition(1, i, k);
        int new_j = axis_addition(0, j, k);
        if(new_i<0 || new_i>=Y_width || new_j<0 || new_j>=X_width)    continue;
        switch( vertex[new_i][new_j]->value){
            case '0':     break;
            case '3':   ;
            case '2':   ;
            case '1':   ;
                _Connect* new_connect = (_Connect*) malloc( sizeof( _Connect));
                new_connect->next = vertex[i][j]->connect;
                new_connect->self = vertex[new_i][new_j];
                new_connect->face = k;
                vertex[i][j]->connect = new_connect;
        }
    }
}
void make_connect_loop(){
    for(int i = 0; i < Y_width; i++)
        for(int j = 0; j < X_width; j++)
            make_connect(i,j);
}
int axis_addition(int axis, int initial, int face){
    int axis_add[2][4] = {0,1,0,-1,  -1,0,1,0};
    return (initial + axis_add[axis][face]);
}
void show(){
    system("CLS");
    for( int i = 0; i < Y_width; i++){
        for( int j = 0; j < X_width; j++){
            switch(vertex[i][j]->value){
            case '0' :  printf("X");    break;
            case '1' :  printf("-");    break;
            case '2' :  printf("o");    break;
            case '3' :  printf("$");    break;
            case '4' :  printf("o");    break;
            case '5' :  printf("@");    break;
            case '6' :  printf("@");    break;
            case '7' :  printf(".");    break;
            }
        }
        printf("\n");
    }
}
bool check_drive(bool offset_or_not,int car_face,int* new_x,int* new_y,int dir,int ofs){
    int direction = ( car_face + dir ) % 4;
    if( offset_or_not)     car_offset(new_x,new_y,car_face,ofs);
    _Connect* temp = vertex[*new_y][*new_x]->connect;
    while( temp && temp->face < direction){
        temp = temp->next;
    }
    if( !temp || temp->face > direction)      return false;
    return true;
}
void car_offset(int* new_x,int* new_y,int car_face,int ofs){
    int offset = ( ( car_face + ofs ) % 4 );
    *new_x = axis_addition(0,*new_x,offset);
    *new_y = axis_addition(1,*new_y,offset);
}
void recursion_show(_Set** S_set, _StepLog* curr){
    if( !curr)      return;
    int j_prime = curr->car->driver->x, i_prime = curr->car->driver->y, face = curr->car->face;
    int l = 0;
    for(; l < 6; l ++){       //see every vertex's fuel;
        if( l == 0){
        }else if( l < 3){car_offset(&j_prime,&i_prime,face,2);
        }else if( l == 3){car_offset(&j_prime,&i_prime,face,1);
        }else{car_offset(&j_prime,&i_prime,face,0);}
        if( vertex[i_prime][j_prime]->visited == false)       break;
    }
    if(l == 6)     return;
    if( !curr->last){
        recursion_show(S_set, curr->last);       //call self;
        update_car(true,curr->car);
        show();
        update_car(false,curr->car);
        recursionUpdate_S(S_set, curr);
        printf("Start!~~\n");
        system("Pause");
        return;
    }
    recursion_show(S_set, curr->last);       //call self;
    update_car(true,curr->car);
    recursionUpdate_S(S_set, curr);
    show();
    Sleep(30);
    update_car(false,curr->car);
    return;
}
void update_car(bool curr_last,_Vehicle* car){
    int i = car->driver->y;
    int j = car->driver->x;
    int k = car->face;
    bool _4 = false;
    if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
    bool _3 = false;
    if(vertex[i][j]->value == '3')      _3 = true;
    vertex[i][j]->value = (curr_last)?(_3)?'6':'5' : (_4)?'3':'7';
    //
    for(int l = 0;l < 2;l ++){
        car_offset(&j,&i,k,2);
        _4 = false;
        if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
        _3 = false;
        if(vertex[i][j]->value == '3')      _3 = true;
        vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'7';
    }
    //
    car_offset(&j,&i,k,1);
    _4 = false;
    if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
    _3 = false;
    if(vertex[i][j]->value == '3')      _3 = true;
    vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'7';

    for(int l = 0;l < 2;l ++){
        car_offset(&j,&i,k,0);
        _4 = false;
        if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
        _3 = false;
        if(vertex[i][j]->value == '3')      _3 = true;
        vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'7';
    }
    return;
}
void reset_vertex(){
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            vertex[i][j]->visited = false;
            if(vertex[i][j]->value == '7')
                vertex[i][j]->value = '1';
        }
    }
    return;
}
//drive
bool drive(int t,_Vehicle* curr_car,_Vehicle* new_car){
    bool (*drive[])(int* car_face,int* new_x,int* new_y) = {
        forward,        backward,        rightshift,
        leftshift,        turnright,        turnleft
    };
    int new_car_face = curr_car->face;
    int new_x = curr_car->driver->x;
    int new_y = curr_car->driver->y;
    if( !(*drive[t])(&new_car_face,&new_x,&new_y) )       return false;  //if can't drive;
    new_car->driver = vertex[new_y][new_x];
    new_car->face = new_car_face;
    return true;
}
bool forward(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(false,*car_face,&new_x_prime,&new_y_prime,0,0) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,0,1) )       return false;
    car_offset(new_x,new_y,*car_face,0);
    return true;
}
bool backward(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    check_drive(true,*car_face,&new_x_prime,&new_y_prime,2,2);
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,2,2) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,2,1) )       return false;
    car_offset(new_x,new_y,*car_face,2);
    return true;
}
bool rightshift(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,1) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,2) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,2) )       return false;
    car_offset(new_x,new_y,*car_face,1);
    return true;
}
bool leftshift(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(false,*car_face,&new_x_prime,&new_y_prime,3,0) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,3,2) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,3,2) )       return false;
    car_offset(new_x,new_y,*car_face,3);
    return true;
}
bool turnright(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,1) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,2) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,1,2) )       return false;
    car_offset(new_x,new_y,*car_face,1);
    car_offset(new_x,new_y,*car_face,1);
    *car_face += 1;
    *car_face %= 4;
    return true;
}
bool turnleft(int* car_face,int* new_x,int* new_y){
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(false,*car_face,&new_x_prime,&new_y_prime,3,0) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,3,2) )       return false;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,3,2) )       return false;
    car_offset(new_x,new_y,*car_face,3);
    car_offset(new_x,new_y,*car_face,2);
    *car_face += 3;
    *car_face %= 4;
    return true;
}
//Q S sets
void print_Q_S(_Set** Q_S_set){
    _Set* tmp;
    for(int i = 0; i < Y_width; i ++){
        for( int j = 0; j < X_width; j ++){
            for(int face = 0; face < 4; ++face){
                tmp = (*(Q_S_set + i*X_width*4 + j*4 + face));
                if( tmp == NULL){
                    printf("N");
                    continue;
                }
                if(!tmp){
                    printf("N");
                    continue;
                }    
                if(tmp->fuel_consumption == -1)        printf("-");
                else        printf("%d",tmp ->fuel_consumption);
            }
            printf(" ");
        }
        printf("\n");
    }
}
void build_Q_set(_Set** Q_set, _Set** S_set, _Vehicle* start){
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            for(int face = 0; face < 4; ++face){
                (*(S_set + i*X_width*4 + j*4 + face )) = NULL;
                if(vertex[i][j]->value == '0'){
                    (*(Q_set + i*X_width*4 + j*4 + face)) = NULL;
                    continue;
                }
                _Set* new_Set = (_Set*)malloc(sizeof(_Set));
                new_Set->fuel_consumption = -1;  //initialization
                //new_Set->num_of_step = 0;
                new_Set->step_log = NULL;
                (*(Q_set + i*X_width*4 + j*4 + face )) = new_Set;
            }
        }
    }
    //update start
    _StepLog* start_step_log = (_StepLog*)malloc(sizeof(_StepLog));
    start_step_log->car = start;
    start_step_log->last = NULL;
    int i = start->driver->y;       int j = start->driver->x;       int face = start->face;
    (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption = 0;
    (*(Q_set + i*X_width*4 + j*4 + face ))->step_log = start_step_log;
    for(int k = 0; k < 2; k ++){
        car_offset(&j,&i,start->face,2);
        (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption = 0;
        (*(Q_set + i*X_width*4 + j*4 + face ))->step_log = start_step_log;
    }
    car_offset(&j,&i,start->face,1);
    (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption = 0;
    (*(Q_set + i*X_width*4 + j*4 + face ))->step_log = start_step_log;
    for(int k = 0; k < 2; k ++){
        car_offset(&j,&i,start->face,0);
        (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption = 0;
        (*(Q_set + i*X_width*4 + j*4 + face ))->step_log = start_step_log;
    }
    return;
}
bool Q_set_all_NULL(_Set** Q_set){
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            for(int face = 0; face < 4; ++face){
                if( !(*(Q_set + i*X_width*4 + j*4 + face )) )      continue;
                return true;
            }
        }
    }
    return false;
}
void catch_Q( _Set** Q_set, int* _i, int* _j, int* _face){
    int oil = 0;
    bool one = true;
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            for(int face = 0; face < 4; ++face){
                if( !(*(Q_set + i*X_width*4 + j*4 + face )) )     //NULL 
                    continue;
                if( (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption == -1)    
                    continue;
                if(one){
                    oil = (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption;
                    *_i = i, *_j = j, *_face = face;
                    one = false;
                }else if( (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption < oil){
                    oil = (*(Q_set + i*X_width*4 + j*4 + face ))->fuel_consumption;
                    *_i = i, *_j = j, *_face = face;
                }
            }
        }
    }
    return;
}
void throw_S(_Set** Q_set, _Set** S_set, int _i, int _j, int _face){
    _Set* curr = *(Q_set + _i*X_width*4 + _j*4 + _face);
    Q_update( Q_set, curr);
    *(S_set + _i*X_width*4 + _j*4 + _face) = curr ;
    *(Q_set + _i*X_width*4 + _j*4 + _face) = NULL;
    printf("\nQ~\n");    print_Q_S(Q_set);    printf("S~\n");    print_Q_S(S_set);    system("CLS");
    return;
}
void Q_update(_Set** Q_set, _Set* curr){
    _Vehicle* car = curr->step_log->car;
    int f, i_prime, j_prime, face_prime;
    _Vertex* tmp = NULL;
    for( int k = 0; k < 6; ++ k){
        _Vehicle* new_car = (_Vehicle*)malloc(sizeof(_Vehicle));
        if( !drive(k, car, new_car) ){      free(new_car);      continue; }
        f = (k<2)?1:(k<4)?2:5;      f += curr->fuel_consumption;
        tmp = new_car->driver;
        i_prime = tmp->y;        j_prime = tmp->x;      /**/face_prime = new_car->face;
        for( int l = 0; l < 6; l ++){       //see every vertex's fuel;
            if( l == 0){
            }else if( l < 3){car_offset(&j_prime,&i_prime,new_car->face,2);
            }else if( l == 3){car_offset(&j_prime,&i_prime,new_car->face,1);
            }else{car_offset(&j_prime,&i_prime,new_car->face,0);}
            if(!(*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime)))        continue;
            if( (*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime))->fuel_consumption != -1
               && f >= (*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime))->fuel_consumption)
                    continue;
            //~~if short than ago;
            _StepLog* new_SL = (_StepLog*)malloc(sizeof(_StepLog));
            new_SL->car = new_car;
            new_SL->last = curr->step_log;
            (*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime))->fuel_consumption = f;
            (*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime))->step_log = new_SL;
            //(*(Q_set + i_prime*X_width*4 + j_prime*4 + face_prime))->num_of_step = curr->num_of_step ++;
        }
    }
    return;
}
//S run
bool S_run(_Set** S_set){
    bool ij_first = true;
    int o, _o;
    _Set* tmp = NULL;
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            if(mission_spot_or_not && vertex[i][j]->value != '3')       continue;
            if( vertex[i][j]->visited )       continue;
            int face = 0;
            bool face_first = true;
            for(int k = 0; k < 4; ++k){     //每個點內看最少油耗的方向
                if( !(*(S_set + i*X_width*4 + j*4 + k)))       continue;
                if(!face_first && _o <= (*(S_set + i*X_width*4 + j*4 + k ))->fuel_consumption)        continue;
                if(face_first)   face_first = false;
                face = k;
                _o = (*(S_set + i*X_width*4 + j*4 + face))->fuel_consumption;
            }
            if( !(*(S_set + i*X_width*4 + j*4 + face)))       continue;
            if(!ij_first && o >= (*(S_set + i*X_width*4 + j*4 + face ))->fuel_consumption)        continue;
            if(ij_first)   ij_first = false;
            tmp = (*(S_set + i*X_width*4 + j*4 + face));
            o = tmp->fuel_consumption;
        }
    }
    if( !tmp){
        printf("\ntmp = NULL!!\n");
        return false;
    }
    recursion_show(S_set, tmp->step_log);
    printf("\nfuel consumption = %d\n",tmp->fuel_consumption);
    return true;
}
bool mission_S_run(_Set** S_set){
    bool ij_first = true;
    int o, _o;
    _Set* tmp = NULL;
    for(int i = 0; i < Y_width; ++i){
        for(int j = 0; j < X_width; ++j){
            if( vertex[i][j]->value != '3')      continue;
            if( vertex[i][j]->visited )       continue;
            int face = 0;
            bool face_first = true;
            for(int k = 0; k < 4; ++k){     //每個點內看最少油耗的方向
                if( !(*(S_set + i*X_width*4 + j*4 + k)))       continue;
                if(!face_first && _o <= (*(S_set + i*X_width*4 + j*4 + k ))->fuel_consumption)        continue;
                if(face_first)   face_first = false;
                face = k;
                _o = (*(S_set + i*X_width*4 + j*4 + face))->fuel_consumption;
            }
            if( !(*(S_set + i*X_width*4 + j*4 + face)))       continue;
            if(!ij_first && o >= (*(S_set + i*X_width*4 + j*4 + face ))->fuel_consumption)        continue;
            if(ij_first)   ij_first = false;
            tmp = (*(S_set + i*X_width*4 + j*4 + face));
            o = tmp->fuel_consumption;
            
        }
    }
    if( !tmp){
        printf("\ntmp = NULL!!\n");
        return false;
    }
    recursion_show(S_set, tmp->step_log);
    printf("\nfuel consumption = %d\n",tmp->fuel_consumption);
    return true;
}
void recursionUpdate_S(_Set** S_set, _StepLog* curr){
    int i_prime = curr->car->driver->y;        int j_prime = curr->car->driver->x;
    int face_prime = curr->car->face;
    for( int l = 0; l < 6; l ++){   //see every vertex's fuel;
        if( l == 0){        
        }else if( l < 3){car_offset(&j_prime,&i_prime,curr->car->face,2);
        }else if( l == 3){car_offset(&j_prime,&i_prime,curr->car->face,1);
        }else{car_offset(&j_prime,&i_prime,curr->car->face,0);}
        if(!(*(S_set + i_prime*X_width*4 + j_prime*4 + face_prime)))        continue;
        vertex[i_prime][j_prime]->visited = true;
    }
}
