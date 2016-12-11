/*
 * main.c
 *
 *  Created on: 2015Äê10ÔÂ8ÈÕ
 *      Author: Dawei
 */


#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"


#define N 10000
#define M 1000000
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


/***************** Main Function *****************\
 *                                                          *
 * Defined below are the Test program of the priority queue *
\************************************************************/


int main(int argc, const char * argv[]) {

    srand((unsigned int)time(NULL));        // seed the random number generator
    void *se=NULL;  //data pointer points to null
    int i,j;
    float sum=0;
    clock_t start,end;
    struct PriorityQueue *FEL = NULL;
    if (FEL == NULL)
         FEL = pq_create();//create an FEL if not exist
    while(pq_size(FEL)<N){
    	double timestamp=randexp(A);
    	pq_push(FEL, timestamp, se);//store N events in the FEL
    }
    for(j=0;j<10;j++){ //for more accurate result
    	start=clock(); // measures the "time" now

		for(i=0;i<M;i++){// for each loop, first delete one event and add another next
			  double Simtime = pq_pop(FEL);
			  double timestamp=Simtime+randexp(A);
			  pq_push(FEL,timestamp,se);
		}
		end=clock();
		clock_t diff=end-start;  // compute time elapsed
		float timeElapsed=diff/(float)CLOCKS_PER_SEC;   // covert to seconds
		float eventdivtime1=2*M/timeElapsed;
	    printf("Time elapsed=%f, Handle %d events, Number of events processed per wallclock time=%f\n", timeElapsed,2*M,eventdivtime1);  // print time elapsed
	    sum=sum+timeElapsed;
    }
    pq_free(FEL);
    float average=sum/10;
    float eventdivtime2=2*M/average;
    printf("Average Time elapsed=%f, Handle %d events, Number of events processed per wallclock time=%f\n", average,2*M,eventdivtime2);// print average time elapse

    return 0;
}



























