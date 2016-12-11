
//  *** HW3 NOT FINISHED YET ***
//  Below is a dijkstra implementation code from http://www.cnblogs.com/skywang12345/p/3711512.html
//  The code did not use priority queue
//  I tried to de-code and implement the algorithm using priority queue but so far in vain
//  Will keep on working the HW3 Version 2 revision
//  ******************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX         100                 // maximum number for graph matrix
#define INF         (~(0x1<<31))        // MAX
#define isLetter(a) ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)   (sizeof(a)/sizeof(a[0]))

// Graph matrix construct
typedef struct _graph
{
    char vexs[MAX];       // vertex
    int vexnum;           // number of vertex
    int edgnum;           // number edges
    int matrix[MAX][MAX]; // graph matrix
}Graph, *PGraph;

Graph* create_example_graph()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    int matrix[][9] = {
                /*A*//*B*//*C*//*D*//*E*//*F*//*G*/
        /*A*/ {   0,  12, INF, INF, INF,  16,  14},
        /*B*/ {  12,   0,  10, INF, INF,   7, INF},
        /*C*/ { INF,  10,   0,   3,   5,   6, INF},
        /*D*/ { INF, INF,   3,   0,   4, INF, INF},
        /*E*/ { INF, INF,   5,   4,   0,   2,   8},
        /*F*/ {  16,   7,   6, INF,   2,   0,   9},
        /*G*/ {  14, INF, INF, INF,   8,   9,   0}};
    
    int vlen = LENGTH(vexs);
    
    int i, j;
    Graph* pG;
    
    // Input number of vertex and edge
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));
    
    // Initialize number of vertex
    pG->vexnum = vlen;
    
    // Vertex initialization
    for (i = 0; i < pG->vexnum; i++)
        pG->vexs[i] = vexs[i];
    
    // Edge initialization
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            pG->matrix[i][j] = matrix[i][j];
    
    // count the number of edges
    for (i = 0; i < pG->vexnum; i++)
        for (j = 0; j < pG->vexnum; j++)
            if (i!=j && pG->matrix[i][j]!=INF)
                pG->edgnum++;
    pG->edgnum /= 2;
    
    return pG;
}


void dijkstra(Graph G, int vs, int prev[], int dist[])
{
    int i,j,k;
    int min;
    int tmp;
    int flag[MAX];      // 1 means visited vertex,
    
    // Initialization
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;              // vertex i not yet visited
        prev[i] = 0;              // previous vertex of i not yet visited
        dist[i] = G.matrix[vs][i];// the distance between vertex i and the previous vertex of it
    }
    
    // startt from vertex "vs"
    flag[vs] = 1;
    dist[vs] = 0;
    
    // go through number of vertex and find the distance
    for (i = 1; i < G.vexnum; i++)
    {
        min = INF;
        for (j = 0; j < G.vexnum; j++)
        {
            if (flag[j]==0 && dist[j]<min)
            {
                min = dist[j];
                k = j;
            }
        }
        // flag vertex as visited
        flag[k] = 1;
        
        // after visited, revise distance to the shortest
        // and set the previous vertex
        for (j = 0; j < G.vexnum; j++)
        {
            tmp = (G.matrix[k][j]==INF ? INF : (min + G.matrix[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp  < dist[j]) )
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
    
    // print out the result
    printf("dijkstra(%c): \n", G.vexs[vs]);
    for (i = 0; i < G.vexnum; i++)
        printf("  shortest(%c, %c)=%d\n", G.vexs[vs], G.vexs[i], dist[i]);
    
}

int main()
{
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    Graph* pG;
    
    pG = create_example_graph();
    dijkstra(*pG, 3, prev, dist);
    
    return 0;
}