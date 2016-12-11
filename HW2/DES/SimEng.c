//
//  SimEng.c

//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SimEng.h"
#include "PriorityQ.h"
#include "FifoQ.h"


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


void runSim(void *D)//run Simulation
{
    struct EventData *data = (struct EventData *) D;
    
    PQinsert(data, data -> param.arrivalEvent.ts);
    
    struct EventData *E = malloc(sizeof(struct EventData));
    

    while (E!=NULL)
    {

    
        E = PQpop();
        
        if (E!=NULL)
        {
        
            if (E -> k == 0)// print out the result
            {
                printf("Aircraft id: %d\n", E -> id);
                printf("Arrival time: %f\n", E -> param.arrivalEvent.ts);
            }
            else
            {
                printf("Aircraft id: %d\n", E -> id);
                printf("Landed time: %f\n", E -> param.landingEvent.ts);
            }

            callback(E);//schedule arrival and landing events
        }
        
        else
            break;
    }

}
