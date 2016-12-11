/*
 * DecisionTreeFunc.c
 *
 *  Created on: 2015Äê11ÔÂ19ÈÕ
 *      Author: Dawei
 */

/* Assumed Data Format:
 *
 *  number of rows, number of columns
 *  7.9,0.18,0.37,1.2,0.04,16,75,0.992,3.18,0.63,10.8,0
 *  6.6,0.16,0.4,1.5,0.044,48,143,0.9912,3.54,0.52,12.4,1
 *	8.3,0.42,0.62,19.25,0.04,41,172,1.0002,2.98,0.67,9.7,0
 *	6.6,0.17,0.38,1.5,0.032,28,112,0.9914,3.25,0.55,11.4,1
 *  ...
 *
 *  each value is separated by comma
 *
 *  functions about how to determine the attribute, how to split, data composition, data description
 */
#include<stdio.h>
#include<stdlib.h>
#include "DecisionTreeFunc.h"
#include <stdbool.h>
#include<math.h>
#include <omp.h>

#include "matrix.h"

struct node{ // node in the tree
	int attr;// attribute that we split for this node
	double median;// median value for that attribute
	int final;//value to check whether it is already done
};

struct node1{
	struct node** array; // array of pointers pointing to each node
	int threshold;//used when reallocating memory
};

double median(matrix x,int row, int column, int num) {
    double temp;
    int i, j;
    // the following two loops sort the array x in ascending order(selection sort)
    for(i=0; i<row-1; i++) {
        for(j=i+1; j<row; j++) {
            if(x[j][num] < x[i][num]) {
                // swap elements
                temp = x[i][num];
                x[i][num] = x[j][num];
                x[j][num] = temp;
            }
        }
    }

    if(row%2==0) {
        // if there is an even number of elements, return mean of the two elements in the middle
        return((x[row/2][num] + x[row/2 - 1][num]) / 2.0);
    } else {
        // else return the element in the middle
        return x[row/2][num];
    }
}

//num specifies the attribute we want to split
matrix splitbymedian(matrix m,unsigned row, unsigned column,unsigned num, bool side){
	double med=median(m,row,column,num);//calculate median
	matrix m1=make_matrix(row/2,column);//smaller matrix
	matrix m2=make_matrix(row-row/2,column);
	int j=0,h=0;
	for(int i=0;i<row;i++){// if smaller than median, this entry goes to m1, if bigger, go to m2
		if(m[i][num]>med){
			for(int k=0;k<column;k++) m2[j][k]=m[i][k];
			j++;
		}else if(m[i][num]<med){
			for(int k=0;k<column;k++) m1[h][k]=m[i][k];
			h++;
		}
	}
	for(int i=0;i<row;i++){//if value equals to median, assign it to m2 first and then m1
		if(m[i][num]==med){
			if(j<row-row/2){
				for(int k=0;k<column;k++) m2[j][k]=m[i][k];
				j++;
			}else{
				for(int k=0;k<column;k++) m1[h][k]=m[i][k];
				h++;
			}
		}
	}


	if(side==0){//side 0--return m1  side 1 -- return m2
		return m1;
	}else{
		return m2;
	}
}

int* label(matrix m,unsigned row){
	int* array=malloc(sizeof(int)*2);
	int count0=0,count1=0;
	for(int i=0;i<row;i++){
		if(m[i][11]==0){
			count0++;
		}else{
			count1++;
		}
	}
	array[0]=count0;
	array[1]=count1;
	return array;// how many 0 and 1 respectively in the matrix-column 11
}
//1.	Calculate the entropy of every attribute in the data set
double entropy(int* Quality){// calculate entropy
	if(Quality[0]==0||Quality[1]==0){
		return 0;
	}
	double entropy=-((double)Quality[0]/(Quality[0]+Quality[1]))*(log2((double)Quality[0]/(Quality[0]+Quality[1])))-((double)Quality[1]/(Quality[0]+Quality[1]))*(log2((double)Quality[1]/(Quality[0]+Quality[1])));
	return entropy;
}

double infogain(int* root, int* left, int* right){// calculate information gain
	double rootentro=entropy(root);
	double leftentro=entropy(left);
	double rightentro=entropy(right);
	double gain=rootentro-((double)(left[0]+left[1]))/(root[0]+root[1])*leftentro-((double)(right[0]+right[1]))/(root[0]+root[1])*rightentro;
	return gain;
}
//2.	Split the dataset into subsets using the attribute for which information gain is maximized.
int bestattr(matrix m,unsigned row,unsigned column,int num){// find the best attribute to split
	double* arraygain=malloc(sizeof(double)*(column-1));
	for(int i=0;i<column-1;i++){
		matrix left=splitbymedian(m,row,column,i,0);
		matrix right=splitbymedian(m,row,column,i,1);
		int* arraytotal=label(m,row);
		int* arrayleft=label(left,row/2);
		int* arrayright=label(right,row-row/2);
		double gain=infogain(arraytotal,arrayleft,arrayright);
		arraygain[i]=gain;
	}
	double max=-10000; int k;
	for(int j=0;j<column-1;j++){// find the largest info gain so as to determine which attribute to split on
		if(arraygain[j]>max&&j!=num ){
			max=arraygain[j];
			k=j;
		}
	}
	return k;

}

struct node1* make_tree(){// make an empty tree
	struct node** arr=malloc(sizeof(struct node*));
	struct node1* arr1=malloc(sizeof(struct node1));
	arr1->array=arr;
	arr1->threshold=0;
	return arr1;
}
//3.	Make a decision tree node containing that attribute.
void create_tree(matrix m,struct node1* array1,unsigned row,unsigned column,int pos,int num){
	struct node* arr=malloc(sizeof(struct node));//allocating memory for a node
	if(m==NULL){
		printf("ERROR: matrix doesn't exist.\n");
		exit(0);
	}
	int* labelcount=label(m,row);//find number of 0's and 1's in the matrix m column 11
	arr->final=2;
	if(array1->threshold<pos+1){// if position go beyond the threshold set before, realloc memory
		array1->array=realloc(array1->array,sizeof(struct node*)*(pos+1));
		array1->threshold=pos+1;
	}
	array1->array[pos]=arr;
	if(labelcount[0]==0){// if all 1, return
		array1->array[pos]->final=1;
		return;//return undetermined.
	}else if(labelcount[1]==0){//if all 0, return
		array1->array[pos]->final=0;
		return;
	}
	int att=bestattr(m,row,column,num);//no 2
	arr->attr=att;
	double med=median(m,row,column,att);
	arr->median=med;// store node attribute
	matrix left=splitbymedian(m,row,column,arr->attr,0);
	matrix right=splitbymedian(m,row,column,arr->attr,1);
	//4.	Do recursions on subsets using remaining attributes.
	create_tree(left,array1,row/2,column,2*pos+1,att);//create subtree on the left branch
	create_tree(right,array1,row-row/2,column,2*pos+2,att);//create subtree on the right branch
	return;
}

int classify(struct node1* array2, double* m,int level){
	if(m==NULL||array2==NULL){
		printf("ERROR: memory allocation wrong.\n");
		exit(0);
	}
	int num=array2->array[level]->final;//check final to see if we have reach the bottom of that branch
	if(num==0){
		return 0;
	}else if(num==1){
		return 1;
	}
	int k=array2->array[level]->attr;
	double med=array2->array[level]->median;
	if(m[k]>med){// if not at the bottom, we need go down to the next level
		level=2*level+2;
		return classify(array2,m,level);
	}else{
		level=2*level+1;
		return classify(array2,m,level);
	}
}

void free_tree(struct node1* array2){
	free(array2->array);
	free(array2);
}


