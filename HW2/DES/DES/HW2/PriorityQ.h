//
//  PriorityQ.h

//

#ifndef PriorityQ_h
#define PriorityQ_h

#include <stdio.h>
#include <stdlib.h>

void PQinsert(void* E, double ts);
/*
 * call function to schedule corresponding arrival and landing event into the future event list
 * @param E is a pointer pointing to the event we want to insert
 * @param ts is the time that event is scheduled
 */
void* PQpop();
/*
 * call function to get the event with highest priority from future event list
 *
 */
#endif /* PriorityQ_h */
