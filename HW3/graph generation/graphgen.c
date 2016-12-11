/*
 * graphgen.c
 *
 *  Created on: 2015Äê10ÔÂ26ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include<stdlib.h>
#include "graphgen.h"


typedef struct ALElement {
    unsigned to;
    struct ALElement *next;
} ALElement;

typedef struct graph{
	int numnode;//number of nodes
	//int numedge;//number of edges
	ALElement ** adjList;
	ALElement * iter;
}graph;

graph* make_graph(unsigned n){
	graph* graphies=malloc(sizeof(graph));
	graphies->numnode=n;
	graphies->adjList=malloc(sizeof(ALElement*)*n);
	unsigned i;
	for(i=0;i<n;i++){
		graphies->adjList[i]=NULL;
	}
	graphies->iter=NULL;
	return graphies;
}

void addEdges(graph* g, unsigned from, unsigned to){
	ALElement* NewNode=malloc(sizeof(ALElement));
	NewNode->to=to;
	NewNode->next=NULL;
	if(g->adjList[from]==NULL){
		g->adjList[from]=NewNode;
	}else{
		g->iter=g->adjList[from];
		while(g->iter->next!=NULL){
			g->iter=g->iter->next;
		}
			g->iter->next=NewNode;
	}

}

void free_graph(graph* g){
	int i;
	for(i=0;i<g->numnode;i++){
		free(g->adjList[i]);
	}
	free(g->iter);
	free(g);
}

void print_graph(FILE* f,graph* g){
	if (f == NULL) {
	    printf("Can't open input file in.list!\n");
	    exit(1);
	  }
	int i;
	for(i=0;i<g->numnode;i++){
		if(g->adjList[i]!=NULL){
			for(g->iter=g->adjList[i];g->iter!=NULL;g->iter=g->iter->next){
				fprintf(f,"%i,%i\n",i,g->iter->to);
			}
		}
	}

}
