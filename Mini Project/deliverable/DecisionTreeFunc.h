/*
 * DecisionTreeFunc.h
 *
 *  Created on: 2015Äê11ÔÂ19ÈÕ
 *      Author: Dawei
 */

#ifndef DECISIONTREEFUNC_H_
#define DECISIONTREEFUNC_H_
#include <stdbool.h>

#include "matrix.h"

typedef struct node1 node1;

/* return an empty tree */
struct node1* make_tree();
/*
 * @parameter m: data matrix
 * @parameter array1: empty tree returned by make_tree()
 * @parameter row: number of rows in the matrix
 * @parameter column: number of columns in the matrix
 * @parameter num: last attribute to split on
 *
 * @return: a tree we could consult later
 */
void create_tree(matrix m,struct node1* array1,unsigned row,unsigned column,int pos,int num);
/*
 * @parameter array2: tree we created in create_tree()
 * @parameter m: one entry of data
 * @parameter level: which level of the tree
 *
 * @return: 0 or 1
 */

int classify(struct node1* array2, double* m,int level);

//free the tree-> array2
void free_tree(struct node1* array2);


#endif /* DECISIONTREEFUNC_H_ */
