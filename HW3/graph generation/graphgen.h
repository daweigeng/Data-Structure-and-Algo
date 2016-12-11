/*
 * main.h
 *
 *  Created on: 2015Äê10ÔÂ26ÈÕ
 *      Author: Dawei
 */

#ifndef GRAPHGEN_H_
#define GRAPHGEN_H_

/* basic directed graph type */
typedef struct graph graph;
/* create a new graph with n vertices and no edges */
graph* make_graph(unsigned N);
/* add an edge to an existing graph */
void addEdges(graph *g, unsigned from, unsigned to);
/* free all space used by graph */
void free_graph(graph *g);
/* breadth first search algorithm */
void print_graph(FILE* f,graph* g);

#endif /* GRAPHGEN_H_ */
