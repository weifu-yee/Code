#ifndef _STRUCT_H_
#define _STRUCT_H_  

using namespace std;

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

#endif