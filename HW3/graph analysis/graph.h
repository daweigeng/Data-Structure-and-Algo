/*
 * graph.h
 *
 *  Created on: 2015Äê10ÔÂ21ÈÕ
 *      Author: Dawei
 */

#ifndef GRAPH_H_
#define GRAPH_H_
/* basic directed graph type */
typedef struct graph graph;
/* create a new graph with n vertices and no edges */
graph* make_graph(unsigned N);
/* add an edge to an existing graph */
void addEdges(graph *g, unsigned from, unsigned to);
/* free all space used by graph */
void free_graph(graph *g);
/* breadth first search algorithm */
int bfs(graph *g,unsigned s);
/* get the first neighbor from the source vertex*/
unsigned first_neighbor(graph *g, unsigned from);
/* get the next neighbor*/
unsigned next_neighbor(graph *g);
/* see whether it touches the end of the linked list*/
int done_neighbor(graph *g);

#endif /* GRAPH_H_ */
