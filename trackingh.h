#ifndef DATA
#define DATA
struct Location{double x; double y;
};

struct point{int id; struct Location p; struct Location direction; double r; double distance; struct point* next;
};

struct points{int length; point list[];
};

struct table{int box; struct point* next;
};
struct idState{int id; int state;
};

struct idNode{int id; struct idNode* next;
};

struct idNodeList{int maxId; idNode* list;
};

typedef struct indNodeList indNodeList;
typedef struct idNode idNode;
typedef struct idState idState;
typedef struct Location Location;
typedef struct point point;
typedef struct points points;
typedef struct table table;
#endif
int inThreshold(Location p,Location t1,Location t2,Location t3,Location t4);
int getId(idNodeList* idList);
void freeId(idNodeList* idList, int id);
idNodeList* makeIdNodeList(void);
void makeIdNode(idNodeList* idList);
void addC(table C[],int index, point data);
void deletC(table C[], int index, int id, point** data);
void addI(table C[],int index, point data);
void deletI(table C[], int index, int id, point** data);
int insertI(table I[],int len, point data,int current);
int isAllZero(table C[],int len);
int inDirection(Location a, Location b);
void initC(table C[],int len);
void initI(table I[],points* past);
double distance(Location zero, Location a);
void tracking(points* current, points* past,idNodeList* idList, double margin, double alpha, double dr,Location t1,Location t2,Location t3,Location t4);
void stateChange(idState stateI[],int id,int state);
void deletAll(table C[],int index);
Location sub(Location a, Location b);
Location normalize(Location a);
double crossMultiple(Location a, Location b);
int ccw(Location a, Location c, Location d);
points* makeInitPoints(int len,Location plist[],idNodeList*idList,double r);
points* makePoints(int len,Location plist[]);
points* makeCurrentToPast(points* current);
void deletAllI(table I[],int index);
