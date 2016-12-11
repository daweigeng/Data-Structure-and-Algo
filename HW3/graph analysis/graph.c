/*
 * graph.c
 *
 *  Created on: 2015Äê10ÔÂ21ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "FIFOQueue.h"

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

int bfs(graph* g,unsigned s){
	if(g->adjList[s]==NULL){
			return 1;
	}
	unsigned* D=malloc(sizeof(unsigned)*g->numnode);
	int* C=malloc(sizeof(int)*g->numnode);
	int i;
	for(i=0;i<g->numnode;i++) C[i]=0;
	for(i=0;i<g->numnode;i++) D[i]=0;
	D[s]=0; C[s]=1;
	FIFOQueue* node=fifo_create();
	fifo_push(node,s);
	while(fifo_size(node)>0){
		unsigned from=fifo_pop(node);
		unsigned n;
		for(n=first_neighbor(g,from);!done_neighbor(g);n=next_neighbor(g)){
			if(C[n]==0){
				D[n]=D[from]+1;
				C[n]=1;
				fifo_push(node,n);
			}
		}
		C[from]=2;
	}
	int sum=0;
	for(i=0;i<g->numnode;i++){
		if(C[i]==2){
			sum=sum+1;
		}
	}
	free(node);
	return sum;
}
unsigned first_neighbor(graph* g, unsigned from){
	g->iter=g->adjList[from];
	return g->iter->to;
}

unsigned next_neighbor(graph *g){
	if(g->iter->next==NULL){
		g->iter=g->iter->next;
		return 0;
	}else{
		g->iter=g->iter->next;
	}
	return g->iter->to;
}

int done_neighbor(graph *g){
	return g->iter==NULL;
}
