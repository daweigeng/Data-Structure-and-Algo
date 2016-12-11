/*
 * Main.c
 *
 *  Created on: 2015Äê10ÔÂ21ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include "graph.h"
#include<stdlib.h>


int main(int argc, const char * argv[]) {
  FILE *graphfile=fopen("C:\\Users\\Dawei\\Desktop\\graph.txt","r");// read file
  if (graphfile == NULL) {
    printf("Can't open input file!\n");
    exit(1);
  }

  unsigned NodesCount,EdgesCount,from, to;
  fscanf(graphfile,"%i,%i",&NodesCount,&EdgesCount); //get the first line
 // graphies->numedge=EdgesCount;

  graph* graphies=make_graph(NodesCount);//make a graph

  int i;
  for(i=0;i<EdgesCount;i++){
     fscanf(graphfile, "%i,%i", &from,&to);
     addEdges(graphies,from,to);
     addEdges(graphies,to,from);
   }// add edges to the graph in the adjacency list format

  int size[NodesCount];
  for(i=0;i<NodesCount;i++){
      size[i]=bfs(graphies,i);
  }//breadth first search algorithm on each vertex

  int max=size[0];
  for(i=0;i<NodesCount;i++){
   	if(size[i]>max){
   		max=size[i];
   			//source=i;
   	 }
  }//find the size as it loops over the source vertex

  printf("the size of the largest component is %i\n",max);
  free_graph(graphies);
  fclose(graphfile);//close the file
  return 0;
}
