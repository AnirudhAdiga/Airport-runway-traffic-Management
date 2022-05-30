#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include"1.h"
int main()
{
    srand(time(NULL)); //to generate random numbers based on the time of the system
    struct airport ap;
    struct plane temp;
    float unit_land,unit_take;
    int i,total_time,cur_time,n,j,k;
    initialize_airport(&ap); //to initialize the queues
    input(&unit_land,&unit_take,&total_time);
    for(cur_time=1;cur_time<=total_time;cur_time++)
    {
        n=randomnumber(unit_land); //generates the number of new planes
        for(i=0;i<n;i++)
        {
            new_plane(&ap,cur_time,1);  //generates the new planes
            if(runway_full(&((&ap)->runway1),1))        // 1 stands for landing in the whole program
                add_to_queue((&(&(&ap)->runway2)->landing),&((&ap)->npln));
            else
                add_to_queue((&(&(&ap)->runway1)->landing),&((&ap)->npln));
        }
        n=randomnumber(unit_take);
        for(i=0;i<n;i++)
        {
            new_plane(&ap,cur_time,2); // 2 stands for takeoff in the whole program
            if(runway_full(&((&ap)->runway2),2))
                add_to_queue((&(&(&ap)->runway1)->takeoff),&((&ap)->npln));
            else
                add_to_queue((&(&(&ap)->runway2)->takeoff),&((&ap)->npln));
        }
        n=0;
        k=2;
        j=2;
        while(n<2)
        {
            if(!(empty_runway(&((&ap)->runway1),1)))         //first priority is given to the planes waiting to land on runway 1
            {
                n++;
                temp=delete_queue(&((&ap)->runway1),1);
                land(&ap,temp,cur_time,n);
                continue;
            }
            else if(!(empty_runway(&((&ap)->runway2),1)))   //second priority to planes waiting to land on runway 2
            {
                n++;
                temp=delete_queue(&((&ap)->runway2),1);
                land(&ap,temp,cur_time,n);
                continue;
            }
            else if(!(empty_runway(&((&ap)->runway2),2))) //Next the planes waiting to take off on runway 2 can do so
            {
                n++;
                temp=delete_queue(&((&ap)->runway2),2);
                fly(&ap,temp,cur_time,j);
                j--;
                continue;
            }
            else if(!(empty_runway(&((&ap)->runway1),2))) //lastly the planes waiting to take off on runway 1 can do so
            {
                n++;
                temp=delete_queue(&((&ap)->runway1),2);
                fly(&ap,temp,cur_time,j);
                j--;
                continue;
            }
            else
            {
                if(n==0)                    //otherwise the runway is declared idle
                    idle(&ap,cur_time);
                n=2;
                continue;
            }
        }
        printf("\n");
    }
    conclude(&ap,total_time);
    return 0;
}
