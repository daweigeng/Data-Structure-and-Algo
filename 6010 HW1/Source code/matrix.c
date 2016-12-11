/*
 * matrix.c
 *
 *  Created on: 2015Äê8ÔÂ31ÈÕ
 *      Author: Dawei
 */
#include "matrix.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

// allocate matrix of size n1*n2
matrix make_matrix(int n1, int n2){
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
int free_matrix(int n1, int n2, matrix a){
	if(n1<=0||n2<=0||a==NULL)
		return 1;  // return failure
	for(int i=0;i<n1;i++)
		free(a[i]);
	free(a);
	return 0;     // return success
}

// compute matrix multiplication
int matrix_multiply(int n1, int n2, int n3, matrix a, matrix b, matrix c){
	if(n1<=0||n2<=0||n3<=0||a==NULL||b==NULL)
		return 1;    // return failure
	int i,j,h;
	for(i = 0;i<n1; i++)
	{
		for(j=0;j<n3;j++)
		{
		   float sum=0;
		   for(h=0;h<n2;h++){
			  sum=sum+a[i][h]*b[h][j];

		   }
		   c[i][j]=sum;
		}
	}

	return 0;    // return success
}

// random fill in matrix of size n1*n2
int matrix_fill_random(int n1,int n2, matrix a){
	if(n1<=0||n2<=0||a==NULL)
		return 1;    // return failure
	int i,j;
	for(i = 0;i<n1; i++){
		for(j = 0;j < n2;j++){
		   a[i][j]=(rand()/(double)RAND_MAX)*20-10;

		}
	}
	return 0;     // return success
}

// print matrix of size n1*n2
int matrix_print(int n1, int n2, matrix a){
	if(n1<=0||n2<=0||a==NULL)
		return 1;   // return failure
	for(int i = 0;i<n1; i++)
	{
		printf("\n");
		for(int j = 0;j < n2;j++)
		{
		   printf("%0.2f ",a[i][j]);
		}
	}
	return 0;    // return success

}
//calculate the time elapsed for matrix multiplication with different dimension
// pretty much go through the same process of the whole library
int matrix_benchmark(int n){
	if(n<=0)
		return 1;  // return failure
	matrix m4=make_matrix(n,n);
	matrix m5=make_matrix(n,n);
	matrix m6=make_matrix(n,n);

	matrix_fill_random(n,n,m4);
	matrix_fill_random(n,n,m5);

	clock_t start,end;
	start=clock();

	printf("Time elapsed for %d dimension matrix is ",n);
	matrix_multiply(n,n,n,m4,m5,m6);

	end=clock();
	clock_t diff=end-start;
	float timeElapsed=diff/(float)CLOCKS_PER_SEC;
	printf(" %.2f\n", timeElapsed);

	free_matrix(n,n,m4);
	free_matrix(n,n,m5);
	free_matrix(n,n,m6);

	return 0;     // return success
}
