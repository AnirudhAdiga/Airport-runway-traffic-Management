#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include"1.h"
void initialize_airport(struct airport* ap)
{
    initialize_runway(&(ap->runway1));
    initialize_runway(&(ap->runway2));
    ap->nplanes = ap->nland = ap->ntakeoff = 0;
    ap->landwait = ap->takeoffwait = ap->idletime = 0;
}
void initialize_runway(struct runway* r)
{
    initialize_queue(&(r->landing));
    initialize_queue(&(r->takeoff));
}
void initialize_queue(struct queue* q)
{
    q->count = 0;
    q->front = 0;
    q->rear = -1;
}
void input(float* unit_land, float* unit_take,int* total_time)
{
    printf("Program to simulate a small busy airport with two runways.\n");
    printf("Runway1 is usually used for landing and Runway 2 is usually used for takeoff.\n");
    printf("Planes arrive ready to land or takeoff at random time.\n");
    printf("If one of the queues is empty,then both runways are used for the other queue.\n");
    printf("If the landing queue is full and another plane arrives to land, then takeoffs will be stopped and both runways are used to clear the backlog of landing planes\n");
    printf("How many units of time do you want the simulation to run?");
    scanf("%d",total_time);
    start:
        printf("Expected number of arrivals per unit time?");
        scanf("%f",unit_land);
        printf("Expected number of departures per unit time?");
        scanf("%f",unit_take);
        printf("\n");
        if (*unit_land<0||*unit_take<0||(*unit_land+*unit_take>1))
        {
            printf("Invalid numbers.\n");
            goto start;
        }
}
int randomnumber(float expect)
{
    int n; //counter of iteration
    double limit,x;// x will be a random number
    again:
    n=0;
    limit = exp(-expect);
    x = rand() / (double) RAND_MAX;
    while (x > limit) {                       //this block of code is to generate a random number
        n++;                                  //which is less than 5 and also to minimize the occurrence of the 3 and 4
        x *= rand() / (double) RAND_MAX;      //so as to not saturate the airport
    }
    if(n>5)
        goto again;
    return n;
}
void new_plane(struct airport* ap, int cur_time,int choice)
{
    (ap->nplanes)++;
    ap->npln.id=ap->nplanes;
    ap->npln.ptime=cur_time;
    if(choice==1)
        printf("Plane %d requesting permission to land.\n", ap->nplanes);
    else if(choice==2)
        printf("Plane %d requesting permission to takeoff.\n", ap->nplanes);
}
int runway_full(struct runway* r,int choice)
{
    if(choice==1)
    {
        if(r->landing.count<5)
            return 0;
        else
            return 1;
    }
    if(choice==2)
    {
        if(r->takeoff.count<5)
            return 0;
        else
            return 1;
    }
}
void add_to_queue(struct queue* q,struct plane* pln)
{
     if (q->count >= 5)
    {
        printf("\nQueue is full.\n");
        return;
    }
    (q->count)++;
    q->rear=(q->rear+1)%5;
    q->p[q->rear]=*pln;
}
int empty_runway(struct runway* r, int choice)
{
    if(choice==1)
    {
        if(r->landing.count==0)
            return 1;
        else
            return 0;
    }
    else if(choice==2)
    {
        if(r->takeoff.count==0)
            return 1;
        else
            return 0;
    }
}
struct plane delete_queue(struct runway* r,int choice)
{
    struct plane p;
    if(choice==1)
        p=del(&(r->landing));
    else if(choice==2)
        p=del(&(r->takeoff));
    return p;
}
struct plane del(struct queue* q)
{
    struct plane p;
    if (q->count<= 0)
    {
        printf("\nQueue is empty.\n");
        p.id=0;
        p.ptime=0;
    }
    else
    {
        (q->count)--;
        p=q->p[q->front];
        q->front=(q->front+1)%5;
    }
    return p;
}
void land(struct airport* ap,struct plane p,int cur_time,int n)
{
    int wait;
    wait=cur_time-p.ptime;
    printf("%d: Plane %d landed on Runway %d ;",cur_time,p.id,n);
    printf("in queue for %d units \n",wait);
    (ap->nland)++;
    (ap->landwait)+= wait;
}
void fly(struct airport* ap,struct plane p,int cur_time,int n)
{
    int wait;
    wait=cur_time-p.ptime;
    printf("%d: Plane %d took off on Runway %d ;",cur_time,p.id,n);
    printf("in queue for %d units \n",wait);
    (ap->ntakeoff)++;
    (ap->takeoffwait)+=wait;
}
void idle(struct airport* ap, int cur_time)
{
    printf("%d: Runway is idle.\n",cur_time);
    (ap->idletime)++;
}
void conclude(struct airport* ap,int endtime)
{
    printf("\tSimulation has concluded after %d units.\n", endtime);
    printf("\tTotal number of planes processed: %d\n", ap->nplanes);
    printf("\tNumber of planes landed: %d\n",ap->nland);
    printf("\tNumber of planes taken off: %d\n",ap->ntakeoff);
    printf("\tNumber left ready to land: %d\n",remain(ap,1));
    printf("\tNumber left ready to take off: %d\n",remain(ap,2));
    if(endtime > 0)
        printf("\tPercentage of time runway idle: %lf \n",((double)ap->idletime/endtime)*100.0);
    if(ap->nland > 0)
        printf("\tAverage wait time to land: %lf \n",((double)ap->landwait/ap->nland));
    if(ap->ntakeoff > 0)
        printf("\tAverage wait time to take off: %lf \n",((double)ap->takeoffwait/ap->ntakeoff));
}
int remain(struct airport* ap, int choice)
{
    int n=0;
    if(choice==1)
    {
        n+=size((&(&ap->runway1)->landing));
        n+=size((&(&ap->runway2)->landing));
    }
    else if(choice==2)
    {
        n+=size(&(&ap->runway1)->takeoff);
        n+=size(&(&ap->runway2)->takeoff);
    }
}
int size(struct queue* q)
{
    return q->count;
}
