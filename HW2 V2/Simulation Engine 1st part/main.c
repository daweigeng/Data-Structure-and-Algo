//
//  main.c
//  Assignment 2
//
//  Created by Karl Gemayel on 9/15/15.
//  Copyright © 2015 Karl Gemayel. All rights reserved.
//

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "SimulationEngine.h"
#include "FIFOQueue.h"
#include "Common.h"

#define VERBOSE                 // comment this command to disable verbose mode

#define R 2						// time runway is used for each landing
#define G 30					// time required on the ground before departing
#define MAX_ARRIVALS 500         // maximum number of aircraft arrivals
#define N 10

/***************** Random Number Generation *****************\
 *                                                          *
 * These functions define how to generate a random number   *
 * from an exponential distribution. Also defined are the   *
 * variables used as the means of the distribution.         *
\************************************************************/


#define A 1                     // mean of exponential distribution

/*
 * Generate a uniform random number in the range [0,1)
 */
double urand(void) {
    double x;
    while ((x = (rand() / (double) RAND_MAX)) >= 1.0);		// loop until x < 1 to exclude 1.0
    return x;
}

/*
 * Generate a random number from an exponential distribution
 * with a given mean.
 *
 * @param mean the mean of the distribution
 * @return a number draw from exponential distribution
 */
double randexp(double mean) {
    return (-1 * mean) * (log(1.0 - urand()));
}




/***************** Events, Handlers, States *****************\
 *                                                          *
 * Defined below are the event handlers, the event types,   *
 * as well as the state variables for the simulation.       *
\************************************************************/

// EventKind: The kinds of events
// RunwayState: The state of the runway
typedef enum {ARRIVAL, LANDED, DISAPPEARED} EventKind;
typedef enum {FREE, BUSY} RunwayState;

// Statistics variables
double  STAT_totalWaitingTime   = 0;                // total waiting time over all aircrafts
int     STAT_numAircrafts       = 0;                // number of aircrafts that have been simulated


// State Variables
int nWaiting = 0;					// number of aircrafts waiting in the air
int nOnGround = 0;                  // number of aircrafts that have landed and are on the ground
int nTotalArrived = 0;              // total number of aircrafts that have arrived till now
RunwayState runwayState = FREE;     // initial runway state


// fifo queue to hold waiting aircrafts
FIFOQueue *inAirQ = NULL;

// Define an aircraft
typedef struct Aircraft {
    int aircraftID;             // aircraft ID
    double startWaiting;        // time when aircraft starts to wait for landing
    double endWaiting;          // time when aircraft stops waiting
} Aircraft;


// define the event data structure
typedef struct EventData {
    EventKind eventKind;
    
    union {
        
        struct {                    // for arrival
            int aircraftID;
        } arrivalEvent;
        
        struct {                    // for landing
            Aircraft *aircraft;
        } landedEvent;
        
        struct {                    // for disappearing
            Aircraft *aircraft;
        } disappearedEvent;
        
    } eventParam;
    
} EventData;


// Event handlers
void arrival        (EventData *e);
void landed         (EventData *e);
void disappeared    (EventData *e);




/********** Function Implementations **********/

// This function is called by the simulation engine, and should process the event
// described by the event data
void callback(void* data) {
    
    EventData* eventData = (EventData*) data;
    
    if (eventData->eventKind == ARRIVAL) {
        arrival(eventData);
    }
    else if (eventData->eventKind == LANDED) {
        landed(eventData);
    }
    else if (eventData->eventKind == DISAPPEARED) {
        disappeared(eventData);
    }
    
}



/*
 * Event handler for an aircraft arrival
 *
 * @param arrivalData the event data
 */
void arrival (EventData *arrivalData) {
    
    
#ifdef VERBOSE
    printf("TS = %f: Aircraft %d: arrived.\n", current_time(), arrivalData->eventParam.arrivalEvent.aircraftID);
    fflush(stdout);
#endif
    
    nWaiting += 1;          // number of aircrafts in the air
    nTotalArrived += 1;     // total number of aircrafts that have arrived
    
    // create an aircraft
    Aircraft* aircraft = (Aircraft *) malloc(sizeof(Aircraft));
    if (aircraft == NULL) FatalError("arrival", "Could not allocate memory for aircraft.");
    
    aircraft->aircraftID = arrivalData->eventParam.arrivalEvent.aircraftID;     // set aircraft ID
    aircraft->startWaiting = current_time();                                    // set time aircraft starts waiting (now)
    
    
    // only schedule a new arrival if the number of aircrafts has not exceeded the maximum allowed
    if (nTotalArrived < MAX_ARRIVALS) {
        
        // Compute the time-stamp of the new arrival,
        double ts = current_time() + randexp(A);
        
        EventData* newArrival = (EventData *) malloc(sizeof(EventData));
        if (newArrival == NULL) FatalError("arrival", "Could not allocate memory for new arrival event.");
        
        newArrival->eventKind = ARRIVAL;
        newArrival->eventParam.arrivalEvent.aircraftID = aircraft->aircraftID+1;
        
        schedule(ts, newArrival);
    }
    
    // check if the runway is free, and schedule departure
    if (runwayState == FREE) {
        
        runwayState = BUSY;                             // runway is now being used by the aircraft
        aircraft->endWaiting = current_time();          // end its waiting time
        
        EventData* newLanded = (EventData *) malloc(sizeof(EventData));
        
        if (newLanded == NULL) FatalError("arrival", "Could not allocate memory for new landed event.");
        
        newLanded->eventKind = LANDED;
        newLanded->eventParam.landedEvent.aircraft = aircraft;
        
        schedule(current_time() + R, newLanded);
    }
    
    // otherwise, runway is busy, so push aircraft onto air queue
    else {
        fifo_push(inAirQ, aircraft);
    }
    
    
    // done with arrival event; free it
    free(arrivalData);
}



/*
 * Event handler for a landed aircraft
 *
 * @param landedData the event data
 */
void landed (EventData *landedData) {
    
#ifdef VERBOSE
    printf("TS = %f: Aircraft %d landed.\n", current_time(), landedData->eventParam.landedEvent.aircraft->aircraftID);
    fflush(stdout);
#endif
    
    
    nWaiting -= 1;          // number of aircrafts in the air decreases
    nOnGround += 1;         // number of aircrafts landed increases
    
    
    // schedule current aircraft to disappear after G seconds
    double ts = current_time() + G;                 // time at which aircraft should "disappear"
    
    EventData *newDisappeared = (EventData *) malloc(sizeof(EventData));
    if (newDisappeared == NULL) FatalError("landed", "Could not allocate memory for disappeared event.");
    
    newDisappeared->eventKind = DISAPPEARED;
    newDisappeared->eventParam.disappearedEvent.aircraft = landedData->eventParam.landedEvent.aircraft;
    
    schedule(ts, newDisappeared);
    
    
    // if there are other aircrafts waiting to land, schedule their landing
    if (nWaiting > 0) {
        
        // remove aircraft from queue
        Aircraft* aircraft = fifo_pop(inAirQ);
        aircraft->endWaiting = current_time();          // end its waiting time
        
        
        EventData *newLanded = (EventData *) malloc(sizeof(EventData));
        if (newLanded == NULL) FatalError("landed", "Could not allocate memory for disappeared event.");
        
        newLanded->eventKind = LANDED;
        newLanded->eventParam.landedEvent.aircraft = aircraft;
        
        schedule(current_time() + R, newLanded);
    }
    // otherwise, free the runway
    else {
        runwayState = FREE;
    }
    
    free(landedData);
}



/*
 * Event handler for a disappeared aircraft
 *
 * @param disappearedData the event data
 */
void disappeared(EventData *disappearedData) {
    nOnGround -= 1;         // aircraft disappears from ground
    
#ifdef VERBOSE
    printf("TS = %f: Aircraft %d disappeared.\n", current_time(), disappearedData->eventParam.disappearedEvent.aircraft->aircraftID);
    fflush(stdout);
#endif
    
    // if you need to get stats from the aircraft (e.g. time it waited in the air),
    // then make sure you get this information here, before freeing the aircraft below.
    Aircraft* aircraft = disappearedData->eventParam.disappearedEvent.aircraft;
    STAT_totalWaitingTime += aircraft->endWaiting - aircraft->startWaiting;     // get waiting time
    STAT_numAircrafts += 1;                                                     // account for aircraft
    
    // free aircraft and event data
    free(disappearedData->eventParam.disappearedEvent.aircraft);
    free(disappearedData);
}



int main(int argc, const char * argv[]) {

    srand((unsigned int)time(NULL));        // seed the random number generator
    
    // create empty aircraft queue
    inAirQ = fifo_create();
    
    
    // Create the first arrival and schedule it
    EventData *arrival = (EventData *) malloc (sizeof(EventData));
    if (arrival == NULL) FatalError("main", "Could not allocate memory for first arrival.");
    
    arrival->eventKind = ARRIVAL;
    arrival->eventParam.arrivalEvent.aircraftID = 0;
    
    double ts = randexp(A);     // set timestamp of first arrival
    
    schedule(ts, arrival);
    
    // start the simulation
    run_sim();
    
    
    printf("Number of aircrafts: %d\n", STAT_numAircrafts);
    printf("Average waiting time: %.2f\n", STAT_totalWaitingTime / STAT_numAircrafts);
    return 0;
}


























