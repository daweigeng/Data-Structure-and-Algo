//
//  main.c

//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SimEng.h"
#include "PriorityQ.h"
#include "FifoQ.h"
#include <math.h>

void callback(void *D);
/*
 * call function to schedule corresponding arrival and landing event
 * @param d is a pointer pointing to the event we want to process
 *
 */
void Arrival(void *d);
/*
 * call function to schedule corresponding arrival event
 * @param d is a pointer pointing to the event we want to process
 *
 */
void Landing(void * d);
/*
 * call function to schedule landing event
 * @param d is a pointer pointing to the event we want to process
 *
 */

int simulationlimit = 500;// we want to 500 airplanes arrive
int intheAir = 0;//to begin with, we have no airplanes in the air
int ontheGround = 0;//no airplanes on the ground either
int runWay = 1; // 0 for busy
double R = 3.0; // the aircraft takes R seconds to land
double U = 10.0; // Set U

//define the structure we are going to use to determine
//which event is happening and extract data from it.
struct EventData{

    enum EventKind {
        arrivalEvent = 0,
        landingEvent = 1
    } k;

    int id;

    union{
        struct{
            double ts;
        }arrivalEvent;

        struct{
            double ts;
        }landingEvent;
    }param;
};

int main(int argc, const char * argv[]) {

    srand((unsigned) time(NULL));

    //create first event
    struct EventData *E = malloc(sizeof(struct EventData));
    E -> k = 0;
    E -> id = 1;
    E -> param.arrivalEvent.ts = 1.0;

    // run Simulation

    runSim(E);

    // free memory
    free(E);
    return 0;
}

double urand(void){
    return (double)rand() / (double)((unsigned)RAND_MAX + 1);
}

double randexp(){
    return -U * (log(1.0-urand()));
}//return simulated interarrival time


void callback(void *D)
{
    struct EventData *data = (struct EventData *) D;
    //if statement to see if this is arrival event or landing event
    if (data -> k == 0)
    {
        Arrival(data);// run arrival function to schedule it into FIFO
    }

    else if (data -> k == 1)
    {
        Landing(data);
    }
}

void Arrival(void *d)
{

    struct EventData *data = (struct EventData *) d;

    intheAir = intheAir + 1;

    if (data -> id < simulationlimit)
    {
    // schedule next arrival
    struct EventData *E = malloc(sizeof(struct EventData));
    E -> k = 0;
    E -> id = data -> id + 1;
    E -> param.arrivalEvent.ts = data -> param.arrivalEvent.ts + randexp();
    PQinsert(E, E -> param.arrivalEvent.ts);
    }
    //printf("schedule arrival event for Aircraft: %d\n", E -> id);
    //printf("With arrival time at: %f\n", E -> param.arrivalEvent.ts);
    //printf("The previous flight arrives at: %f\n", data -> param.arrivalEvent.ts);


    if (runWay == 0)
    {
        FIFOinsert(data, data -> param.arrivalEvent.ts);
    }
    else
    {
        data -> k = 1;
        data -> param.landingEvent.ts = data -> param.arrivalEvent.ts + R;
        PQinsert(data, data -> param.landingEvent.ts);
        runWay = 0;
    }


    //free(E);
}

void Landing(void * d)
{

    intheAir = intheAir - 1;

    if (intheAir > 0)
    {
        struct EventData *E = malloc(sizeof(struct EventData));

        E = FIFOpop();//get the first plane
        E -> k = 1;
        E -> param.landingEvent.ts = E -> param.arrivalEvent.ts + R;
        PQinsert(E, E->param.landingEvent.ts);
    }
    else
    {
        runWay = 1;//set runway free
    }
}





