#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define MAX 5
typedef struct queue 
{
  
int plane;
   
struct queue *next;
} plane_queue;

void Init_simulation (int *, double *, double *);

void new_plane (plane_queue **, plane_queue **, int);

int del_plane (plane_queue **, plane_queue **);

int count (plane_queue **);

int random (double);

int
main () 
{
  
int simulation_time, plane_no = 1;
  
double probability_takeoff, prbability_landing;
  
int rand_landings, rand_takeoffs;
  
Init_simulation (&simulation_time, &probability_takeoff,
		    &prbability_landing);
  
plane_queue * land_front = NULL;
  
plane_queue * land_rear = NULL;
  
plane_queue * takeoff_front = NULL;
  
plane_queue * takeoff_rear = NULL;
  
for (int T = 1; T <= simulation_time; T++)
    
    {
      
rand_takeoffs = random (probability_takeoff);
      
for (int planes = 0; planes < rand_takeoffs; planes++)
	
	{
	  
printf ("plane %d is ready to takeoff\n", plane_no);
	  
if ((count (&takeoff_front)) <= MAX)
	    
new_plane (&takeoff_front, &takeoff_rear, plane_no);
	  
	  else
	    
	    {
	      
printf ("plane %d is told to wait\n", plane_no);
	      
new_plane (&takeoff_front, &takeoff_rear, plane_no);
	    
}
	  
plane_no++;
	
}
      
rand_landings = random (prbability_landing);
      
for (int planes = 0; planes < rand_landings; planes++)
	
	{
	  
printf ("plane %d is ready to land\n", plane_no);
	  
new_plane (&land_front, &land_rear, plane_no);
	  
plane_no++;
      
} 
if ((count (&land_front) > MAX))
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d landed using runway 1\n",
		   del_plane (&land_front, &land_rear 
));
	  
printf ("plane %d landed using runway 2\n",
		   del_plane (&land_front, &land_rear 
));
	
}
      
      else if ((count (&land_front) <= MAX && count (&land_front) > 0)
	       && (count (&
takeoff_front) > 0))
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d took off using runway 2\n",
		   del_plane (&takeoff_front, &
takeoff_rear));
	  
printf ("plane %d landed using runway 1\n",
		   del_plane (&land_front, &land_rear 
));
	
}
      
      else if (count (&land_front) > 1 && count (&takeoff_front) == 0)
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d landed using runway 1\n",
		   del_plane (&land_front, &land_rear 
));
	  
printf ("plane %d landed using runway 2\n",
		   del_plane (&land_front, &land_rear 
));
	
}
      
      else if (count (&takeoff_front) > 1 && count (&land_front) == 0)
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d took off using runway 1\n",
		   del_plane (&takeoff_front, &
takeoff_rear));
	  
printf ("plane %d took off using runway 2\n",
		   del_plane (&takeoff_front, &
takeoff_rear));
	
}
      
      else if (count (&takeoff_front) == 1 && count (&land_front) == 0)
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d took off using runway 2\n",
		   del_plane (&takeoff_front, &
takeoff_rear));
	
}
      
      else if (count (&land_front) == 1 && count (&takeoff_front) == 0)
	
	{
	  
printf ("\n%d\n", T);
	  
printf ("plane %d landed using runway 1\n",
		   del_plane (&land_front, &land_rear 
));
	
}
      
      else
	
	{
	  
printf ("\n%d:\n", T);
	  
printf ("Runways are idle\n");
	
}
    
}
  
return 0;
}


void
Init_simulation (int *simulation_time, double *probability_takeoff,
		 double *
prbability_landing)
{
  
printf ("How many units of time will the simulation run?");
  
scanf ("%d", simulation_time);
  
printf ("Expected number of arrivals per unit time: ");
  
scanf ("%lf", prbability_landing);
  
printf ("Expected number of departures per unit time: ");
  
scanf ("%lf", probability_takeoff);

} 
int

random (double expect)
{
  
int n = 0;
  
float x = rand () / (double) RAND_MAX;
  
while (x > exp (-(expect * 2)))
    
    {
      
n++;
      
x *= rand () / (double) RAND_MAX;
    
} 
return n;
}


void
new_plane (plane_queue ** front, plane_queue ** rear, int x)
{
  
plane_queue * temp = (plane_queue *) malloc (sizeof (plane_queue));
  
temp->plane = x;
  
temp->next = NULL;
  
if (*front == NULL && *rear == NULL)
    
    {
      
*front = temp;
      
*rear = temp;
    
}
  
  else
    
    {
      
(*rear)->next = temp;
      
*rear = temp;
    
}

}


int
del_plane (plane_queue ** front, plane_queue ** rear)
{
  
plane_queue * temp = (plane_queue *) malloc (sizeof (plane_queue));
  
if (*front == *rear)
    
    {
      
temp = *front;
      
*front = NULL;
      
*rear = NULL;
      
return temp->plane;
    
}
  
  else if (*front != *rear)
    
    {
      
temp = *front;
      
*front = (*front)->next;
      
return temp->plane;
    
}

}


int
count (plane_queue ** front)
{
  
int count = 0;
  
plane_queue * temp = (plane_queue *) malloc (sizeof (plane_queue));
  
temp = *front;
  
while (temp != NULL)
    
    {
      
count++;
      
temp = temp->next;
    
}
  
return count;
}
