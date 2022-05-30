struct plane
{
    int id;
    double ptime;
};
struct queue
{
    int count;
    int front;
    int rear;
    struct plane p[5];
};
struct runway
{
    struct queue takeoff;
    struct queue landing;
};
struct airport
{
    struct runway runway1;
    struct runway runway2;
    int idletime;
    int landwait, takeoffwait;
    int nland, nplanes, ntakeoff;
    struct plane npln;
};
void input(float* unit_land,float* unit_take,int* total_time);
void initialize_airport(struct airport* ap);
void initialize_runway(struct runway* r);
void initialize_queue(struct queue* n);
int randomnumber(float expect);
void new_plane(struct airport* ap, int curtime,int choice);
int runway_full(struct runway* r,int choice);
void add_to_queue(struct queue* q,struct plane* pln);
int empty_runway(struct runway* r, int choice);
struct plane delete_queue(struct runway* r,int choice);
struct plane del(struct queue* q);
void land(struct airport* ap, struct plane p, int curtime,int n);
void fly(struct airport* ap,struct plane p,int curtime,int n);
void idle(struct airport* ap, int curtime);
void conclude(struct airport* ap, int endtime);
int remain(struct airport* ap, int choice);
int size(struct queue* q);
