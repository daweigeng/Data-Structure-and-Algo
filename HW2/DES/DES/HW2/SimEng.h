//
//  SimEng.h

//

#ifndef SimEng_h
#define SimEng_h

#include <stdio.h>
#include <stdlib.h>

void runSim(void *d);
/*
 * run simulation
 * @param d is a pointer pointing to the first event
 *
 */

double urand(void);
double randexp();
/*
 * call function to generate interarrival time
 *
 *
 */

#endif /* SimEng_h */
