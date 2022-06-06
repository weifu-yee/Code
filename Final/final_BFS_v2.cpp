#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~FILE~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
FILE* file(){
    FILE* inf = fopen("D:/Code/Final/input1 copy.txt","r");
    return inf;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Structures~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
typedef struct _Vertex{
    char value;
    int x;
    int y;
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
typedef struct _Queue{
    _Vehicle* car;
    int fuel_consumption;
    int num_of_step;
    struct _StepLog* step_log;
    struct _Queue* queue_next;
    struct _Unvisited* unvisited;
}_Queue;
typedef struct _StepLog{
    _Vehicle* car;
    struct _StepLog* last;
}_StepLog;
typedef struct _Unvisited{
    _Vertex* vertex;
    struct _Unvisited* next;
}_Unvisited;
typedef struct _SuccessStepLog{
    int fuel_consumption;
    int num_of_step;
    struct _StepLog* head;
}_SuccessStepLog;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Global Variables~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vertex* vertex[50][50];    //the map's vertex which input;
int X_width, Y_width;       //X,Y width
bool mission_spot_or_not = false;
_Queue* front = NULL;
_Queue* rear = NULL;
int best_step;
//int fff = 0;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function declaration~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vehicle* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void make_connect_loop();     //loop to make junction
int axis_addition(int axis, int initial, int face);
void show();        //print the graph
void update_car(bool curr_last,_Vehicle* car);
int run(_Vehicle* start);       //run from the start;
_Unvisited* build_unvisited();
_Unvisited* copy_unv(_Unvisited* curr);
void recursion_copy(_Unvisited* curr,_Unvisited** new_head_of_unv);
bool finish_or_not();       //check if we get it;
void enqueue(_Vehicle* car,_StepLog* step_log,int num_of_step,
             int fuel_consumption,_Unvisited* unvisited);
bool dequeue(_SuccessStepLog** succ);
void delete_unv(_Vehicle* car,_Unvisited** ptr_unv,int t);
_Unvisited* triversal_delete(_Vertex* vertex,_Unvisited* unv);
void recursion_free(_Unvisited* To_free);
bool forward(int* car_face,int* new_x,int* new_y);
bool backward(int* car_face,int* new_x,int* new_y);
bool rightshift(int* car_face,int* new_x,int* new_y);
bool leftshift(int* car_face,int* new_x,int* new_y);
bool turnright(int* car_face,int* new_x,int* new_y);
bool turnleft(int* car_face,int* new_x,int* new_y);
bool check_drive(bool offset_or_not,int car_face,int* new_x,int* new_y,int dir,int ofs);
void car_offset(int* new_x,int* new_y,int car_face,int ofs);
void Verify_drive(int t,int X,int Y,int face);
void recursion_show(_StepLog* curr);

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function wrappers~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
bool drive(int t,_Vehicle* curr_car,_Vehicle* new_car){
    bool (*drive[])(int* car_face,int* new_x,int* new_y) = {
        forward,
        backward,
        rightshift,
        leftshift,
        turnright,
        turnleft
    };
    int new_car_face = curr_car->face;
    int new_x = curr_car->driver->x;
    int new_y = curr_car->driver->y;
    if( !(*drive[t])(&new_car_face,&new_x,&new_y) )       return false;  //if can't drive;
    new_car->driver = vertex[new_y][new_x];
    new_car->face = new_car_face;
    return true;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~main~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
int main(){
    _Vehicle* start = Adjacency_List();
    make_connect_loop();
    if( run(start) )
        printf("best_step:%d",best_step);
    printf((mission_spot_or_not)?"\nmission~":"\nall~");
    return 0;
}

int main2(){
    _Vehicle* start = Adjacency_List();
    make_connect_loop();
    update_car(true,start);
    show();
    system("Pause");
    _StepLog* curr = (_StepLog*)malloc(sizeof(_StepLog));
    curr->car = (_Vehicle*)malloc(sizeof(_Vehicle));
    curr->car->driver = vertex[8][4];
    curr->car->face = 0;
    curr->last = (_StepLog*)malloc(sizeof(_StepLog));
    curr->last->car = (_Vehicle*)malloc(sizeof(_Vehicle));
    curr->last->car->driver = vertex[7][4];
    curr->last->car->face = 0;
    curr->last->last = (_StepLog*)malloc(sizeof(_StepLog));
    curr->last->last->car = (_Vehicle*)malloc(sizeof(_Vehicle));
    curr->last->last->car->driver = vertex[8][5];
    curr->last->last->car->face = 1;
    curr->last->last->last = NULL;
    printf("aa");
    recursion_show(curr);

    return 0;
}

// int main(){
//     _Vehicle* start = Adjacency_List();
//     make_connect_loop();
//     update_car(false,start);
//     update_car(true,start);
//     show();
//     system("Pause");
//     Verify_drive(3,start->driver->x,start->driver->y-3,start->face);
//     show();
//     // show();
//     // system("Pause");
//     // update_car(true,start);
//     // show();
//     // system("Pause");
//     // update_car(false,start);
//     // show();
//     return 0;
// }

_Vehicle* Adjacency_List(){
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
            if(vertex[i][j]->value == '0')
                printf("X");
            else if(vertex[i][j]->value == '1')
                printf("-");
            else if(vertex[i][j]->value == '2')
                printf("o");
            else if(vertex[i][j]->value == '3')
                printf("$");
            else if(vertex[i][j]->value == '4')
                printf("o");
            else if(vertex[i][j]->value == '5')
                printf("@");
            else if(vertex[i][j]->value == '6')
                printf("@");
        }
        printf("\n");
    }
    //Sleep(300);
}
void update_car(bool curr_last,_Vehicle* car){
    int i = car->driver->y;
    int j = car->driver->x;
    int k = car->face;
    bool _4 = false;
    if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
    bool _3 = false;
    if(vertex[i][j]->value == '3')      _3 = true;
    vertex[i][j]->value = (curr_last)?(_3)?'6':'5' : (_4)?'3':'1';
    for(int l = 0;l < 2;l ++){
        car_offset(&j,&i,k,2);
        _4 = false;
        if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
        _3 = false;
        if(vertex[i][j]->value == '3')      _3 = true;
        vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'1';
    }
    car_offset(&j,&i,k,1);
    _4 = false;
    if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
    _3 = false;
    if(vertex[i][j]->value == '3')      _3 = true;
    vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'1';
    for(int l = 0;l < 2;l ++){
        car_offset(&j,&i,k,0);
        _4 = false;
        if(vertex[i][j]->value == '4' || vertex[i][j]->value == '6')      _4 = true;
        _3 = false;
        if(vertex[i][j]->value == '3')      _3 = true;
        vertex[i][j]->value = (curr_last)?(_3)?'4':'2' : (_4)?'3':'1';
    }
    return;
}
int run(_Vehicle* start){
    _Unvisited* start_unvisited = build_unvisited();
    _StepLog* start_step_log = (_StepLog*)malloc(sizeof(_StepLog));
    start_step_log->car = start;
    start_step_log->last = NULL;
    enqueue(start,start_step_log,0,0,start_unvisited);
    _SuccessStepLog* succ = (_SuccessStepLog*)malloc(sizeof(_SuccessStepLog));
    while( dequeue(&succ));
    best_step = succ->num_of_step;
    system("Pause");
    recursion_show(succ->head);
    return 1;
}
_Unvisited* build_unvisited(){
    _Unvisited* head_of_unvis = NULL;
    for( int i = 0; i < Y_width; i ++){
        for( int j = 0; j < X_width; j ++){
            if( vertex[i][j]->value == '0')
                continue;
            if( vertex[i][j]->value == '2')
                    continue;
            if( mission_spot_or_not){
                if( vertex[i][j]->value == '1')
                    continue;
            }
            _Unvisited* new_unvisited = (_Unvisited*)malloc(sizeof(_Unvisited));
            new_unvisited->next = head_of_unvis;
            new_unvisited->vertex = vertex[i][j];
            head_of_unvis = new_unvisited;
        }
    }
    return head_of_unvis;
}
_Unvisited* copy_unv(_Unvisited* curr){
    _Unvisited* new_head_of_unv = NULL;
    recursion_copy(curr,&new_head_of_unv);
    return new_head_of_unv;
}
void recursion_copy(_Unvisited* curr,_Unvisited** ptr_new_head_of_unv){
    if( curr->next)
        recursion_copy(curr->next,ptr_new_head_of_unv);
    _Unvisited* new_unv = (_Unvisited*)malloc(sizeof(_Unvisited));
    new_unv->next = *ptr_new_head_of_unv;
    new_unv->vertex = curr->vertex;
    *ptr_new_head_of_unv = new_unv;
    return;
}
bool finish_or_not(){
    for( int i = 0; i < Y_width; i ++){
        for( int j = 0; j < X_width; j ++){
            if( vertex[i][j]->value == ( (mission_spot_or_not)?'3':'1'))
                return false;
        }
    }
    return true;
}
void enqueue(_Vehicle* car,_StepLog* step_log,int num_of_step,int fuel_consumption,_Unvisited* unvisited){
    _Queue* new_queue = (_Queue*)malloc(sizeof(_Queue));
    if( rear)       rear->queue_next = new_queue;
    else    front = new_queue;      //initialization;
    rear = new_queue;
    new_queue->car = car;
    new_queue->step_log = step_log;
    new_queue->fuel_consumption = fuel_consumption;
    new_queue->num_of_step = num_of_step;
    new_queue->unvisited = unvisited;
    new_queue->queue_next = NULL;
    //fff++;
}
bool dequeue(_SuccessStepLog** succ){
    //Sleep(10);
    //system("Pause");
    update_car(true,front->car);
    show();
    update_car(false,front->car);
    _Unvisited* ddddd = front->unvisited;
    // while(ddddd){
    //     printf("(%d,%d)",ddddd->vertex->x,ddddd->vertex->x);
    //     ddddd = ddddd->next;
    // }

    if( !front)      return false;
    if( front->unvisited == NULL){
        ( *succ)->fuel_consumption = front->fuel_consumption;
        ( *succ)->num_of_step = front->num_of_step;
        ( *succ)->head = front->step_log;
        return false;
    }
    bool another_t = false;
    int temp_t = -1;     //to save the t that same with front->car;
    _Vehicle* curr_car = front->car;
    int new_num_of_step = front->num_of_step + 1;
    int new_fuel_consumption;
    for(int t = 0; t <= 5 ; t ++){
        _Vehicle* new_car = (_Vehicle*)malloc(sizeof(_Vehicle));
        if( !drive(t,curr_car,new_car)){        //if it can't go;
            free(new_car);
            continue;
        }
        _StepLog* new_step_log = (_StepLog*)malloc(sizeof(_StepLog));
            new_step_log->car = new_car;
            new_step_log->last = front->step_log;
        _Unvisited* new_unvisited = copy_unv(front->unvisited); //establish a new and same unv;
        delete_unv(new_car,&new_unvisited,t);
        {if( t >= 4)      //classify fuel_cons
            new_fuel_consumption = front->fuel_consumption + 5;
        else if( t >= 2)
            new_fuel_consumption = front->fuel_consumption + 2;
        else
            new_fuel_consumption = front->fuel_consumption + 1;}
        if( front->step_log->last){
            if( new_car->driver->x == front->step_log->last->car->driver->x)
            if( new_car->driver->y == front->step_log->last->car->driver->y)
            if( new_car->face == front->step_log->last->car->face){
                if( !another_t)     
                    temp_t = t;        //if not yet other t;
                continue;
            }     
        }   
        enqueue( new_car, new_step_log, new_num_of_step,
                 new_fuel_consumption, new_unvisited);
        another_t = true;
        }
    if(temp_t >= 0 && !another_t){        //when a die path only can back;
            _Vehicle* new_car = (_Vehicle*)malloc(sizeof(_Vehicle));
            drive(temp_t,curr_car,new_car);
            _StepLog* new_step_log = (_StepLog*)malloc(sizeof(_StepLog));
                new_step_log->car = new_car;
                new_step_log->last = front->step_log;
            _Unvisited* new_unvisited = copy_unv(front->unvisited);
            delete_unv(new_car,&new_unvisited,temp_t);
            if( temp_t >= 4)     new_fuel_consumption = front->fuel_consumption + 5;
            else if( temp_t >= 2)     new_fuel_consumption = front->fuel_consumption + 2;
            else      new_fuel_consumption = front->fuel_consumption + 1;
            enqueue( new_car, new_step_log, new_num_of_step,
                 new_fuel_consumption, new_unvisited);
        }
    _Queue* To_free = front;
    recursion_free(front->unvisited);
    front = front->queue_next;
    free( To_free);
    return true;
}
void delete_unv(_Vehicle* car,_Unvisited** ptr_unv,int t){
    _Unvisited* unv = *ptr_unv;
    int new_x = car->driver->x;
    int new_y = car->driver->y;
    switch( t){
    case 0 :
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,1);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        break;
    case 1 :
        car_offset(&new_x,&new_y,car->face,2);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,1);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        break;
    case 2 :
        car_offset(&new_x,&new_y,car->face,1);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        break;
    case 3 :
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        break;
    case 4 :
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,2);
        unv = triversal_delete(vertex[new_y][new_x],unv);
        break;
    case 5 :
        unv = triversal_delete(vertex[new_y][new_x],unv);
        car_offset(&new_x,&new_y,car->face,0);
        unv = triversal_delete(vertex[new_y][new_x],unv);
    }
    *ptr_unv = unv;
    return;
}
_Unvisited* triversal_delete(_Vertex* vertex,_Unvisited* unv){
    if( !unv)     return NULL;
    _Unvisited* temp = triversal_delete(vertex,unv->next);
    if( vertex == unv->vertex)      return temp;
    unv->next = temp;
    return unv;
}
void recursion_free(_Unvisited* To_free){
    if( To_free->next)
        recursion_free( To_free->next);
    free(To_free);
    return;
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
void Verify_drive(int t,int X,int Y,int face){
    _Vehicle verify_car = {vertex[Y][X],face};
    printf("drive[%d]--(%d,%d) face to: %d \t~",t,X,Y,face);
    if( drive(t,&verify_car,&verify_car)){
        printf("Yes");
    }else{
        printf("No");
    }
    return;
}
void recursion_show(_StepLog* curr){
    if( !curr)      return;
    if( !curr->last){
        recursion_show(curr->last);       //call self;
        update_car(true,curr->car);
        show();
        Sleep(300);
        update_car(false,curr->car);
        printf("Start!~~\n");
        system("Pause");
        return;
    }
    recursion_show(curr->last);       //call self;
    update_car(true,curr->car);
    show();
    Sleep(300);
    update_car(false,curr->car);
    return;
}
