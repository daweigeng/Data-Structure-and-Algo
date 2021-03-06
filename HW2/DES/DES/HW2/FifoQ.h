//
//  FifoQ.h


//

#ifndef FifoQ_h
#define FifoQ_h

#include <stdio.h>
#include <stdlib.h>


void FIFOinsert(void* E, double ts);
/*
 * call function to schedule plane into FIFO queue
 * @param E is a pointer pointing to the event we want to insert
 * @param ts is the time that event is scheduled
 */

void* FIFOpop();
/*
 * call function to get rid of the first in-list plane
 */

#endif /* FifoQ_h */
