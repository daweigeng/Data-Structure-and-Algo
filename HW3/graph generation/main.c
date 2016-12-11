/*
 * main.c
 *
 *  Created on: 2015Äê10ÔÂ26ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include<stdlib.h>
#include "graphgen.h"
#include <time.h>

int main(int argc, const char * argv[]) {
	int N,i,j;
	int Edgecount=0;
	double p;
	sscanf(argv[1],"%d",&N);
	sscanf(argv[2],"%lf",&p);

	graph* graph=make_graph(N);

	srand((unsigned)time(NULL));

	for(i=0;i<N;i++){
		for(j=i+1;j<N;j++){
			double RandomP=rand()/(double)RAND_MAX;
			if(RandomP<p){
				addEdges(graph,i,j);
				addEdges(graph,j,i);
				Edgecount+=2;
			}
		}
	}
	char filename;
	sscanf(argv[3],"%s",&filename);
	FILE *f=fopen(&filename,"w");
	fprintf(f,"%d,%d\n",N,Edgecount);
	print_graph(f,graph);
	free_graph(graph);
	fclose(f);
	return 0;

}

