/*
 * Generator.c
 *
 *  Created on: 2015Äê10ÔÂ30ÈÕ
 *      Author: Dawei
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float cumfreq(int* FreqArray, int n){
	if(n<0) return 0;
	int i;float s=0;
	for(i=0; i<=n;i++){
		s=s+FreqArray[i];
	}
	return s;
}

int main(int argc, const char * argv[]) {
    
    // if number of input args not met, quit
    if (argc != 3) {
        return 0;
    }

    srand(time(NULL));
    size_t numNodes = (size_t) strtoul (argv[1], NULL, 10);     // num nodes
    const char* fname = argv[2];
    
    // open file for writing

    int i,n,to,sum=0,size=5;
    int* FreqArray=malloc(sizeof(int)*size);
    for(i=0;i<5;i++) {
    	FreqArray[i]=4;
    	sum=sum+FreqArray[i];
    }//initialization of fully connected graph

    // write number of nodes
    FILE* fp = fopen(fname, "w");
    fprintf(fp, "%d\n", numNodes);

    for (n = 1; n < numNodes; n++) {
    	double p = rand() / (double) RAND_MAX;// random number
        for (to = 0; to < n; to++) {

        	double weight = rand() / (double) RAND_MAX;//weight

            if (n<5) {
                fprintf(fp, "%d %d %lf\n", n, to, weight);// fully connected graph
            }else{
            	//if p fall into corresponding interval, then there is an edge between
            	if(cumfreq(FreqArray,to-1)/sum <p && p<cumfreq(FreqArray,to)/sum){
            			fprintf(fp, "%d %d %lf\n", n, to, weight);
            			FreqArray[to]=FreqArray[to]+1;// frequency matrix change
            	}
            }
        }
        if(n>=5){
        	size=size+1;//size is the number of vertices
        	FreqArray=realloc(FreqArray,sizeof(int)*size);// reallocating memory
        	FreqArray[size-1]=1;//only one connection for new node
        	sum=sum+2;//total edge takes new vertex into consideration
        }

    }
    free(FreqArray);
    fclose(fp);
    return 0;
}
