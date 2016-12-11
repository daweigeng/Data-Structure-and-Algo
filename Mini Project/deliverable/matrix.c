/*
 * data.c
 *
 *  Created on: 2015Äê11ÔÂ19ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include<stdlib.h>
#include "DecisionTreeFunc.h"
#include "matrix.h"

matrix make_matrix(int n1, int n2){// make an empty matrix of size n1*n2
	if(n1<=0||n2<=0)
		return NULL;
	matrix m=(matrix)malloc(n1*sizeof(double*));

	int i;
	for(i=0;i<n1;i++){
		m[i]=(double*)malloc(n2*sizeof(double));
	}

	return m;
}
// free matrix
int free_matrix(int n1, int n2, matrix a){//free matrix memory
	if(n1<=0||n2<=0||a==NULL)
		return 1;  // return failure
	for(int i=0;i<n1;i++)
		free(a[i]);
	free(a);
	return 0;     // return success
}

void matrix_print(int n1, int n2, matrix a){//print matrix

	for(int i = 0;i<n1; i++)
	{
		printf("\n");
		for(int j = 0;j < n2;j++)
		{
		   printf("%0.4f ",a[i][j]);
		}
	}
	return;    // return success

}

matrix ReadData(FILE* dataset,unsigned line, unsigned column){//read data from text file into matrix

	 matrix m=make_matrix(line,column);
	if (m == NULL) {
		printf("ERROR: Could not allocate enough space.\n");
		exit(0);
	}
	 double a,b,c,d,e,f,g,h,n,j,k,l;
	 for(int i=0;i<line;i++){
		 fscanf(dataset,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",&a,&b,&c,&d,&e,&f,&g,&h,&n,&j,&k,&l);
		 m[i][0]= a;m[i][1]= b;m[i][2]= c;m[i][3]= d;m[i][4]= e;m[i][5]= f;m[i][6]= g;m[i][7]= h;m[i][8]= n;
		 m[i][9]= j;m[i][10]= k;m[i][11]= l;
		 }
	 return m;
}

