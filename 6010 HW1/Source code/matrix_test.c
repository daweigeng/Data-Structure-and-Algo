/*
 * main.c
 *
 *  Created on: 2015Äê8ÔÂ31ÈÕ
 *      Author: Dawei
 */
#include<stdio.h>
#include"matrix.h"
#include<stdlib.h>
#include<time.h>
int main(int argc,const char*argv[]){
	int n1=4,n2=3,n3=2;

	matrix m1=make_matrix(4,3); // allocate space for our first matrix
	matrix m2=make_matrix(3,2); // allocate space for our second matrix
	matrix m3=make_matrix(4,2); // allocate space for our third matrix

	 // check memory errors
	if (m1 == NULL||m2==NULL) {
		printf("ERROR: Could not allocate enough space.\n");
		exit(0);
	}
    srand((unsigned)time(NULL)); // seed our random number generator

    // fill the two allocated matrices with random numbers
	matrix_fill_random(n1,n2,m1);
	matrix_fill_random(n2,n3,m2);

	// print the two matrices
	printf("m1:");matrix_print(n1,n2,m1);
	printf("\nm2:");matrix_print(n2,n3,m2);

	clock_t start,end;
	start=clock(); // measures the "time" now

    printf("\nProduct:");
    matrix_multiply(n1,n2,n3,m1,m2,m3); // compute their product
    matrix_print(n1,n3,m3);

    end=clock();
    clock_t diff=end-start;  // compute time elapsed
    float timeElapsed=diff/(float)CLOCKS_PER_SEC;   // covert to seconds
    printf("\nTime elapsed=%.2f\n", timeElapsed);  // print time elapsed

    // free the memory allocated for the two matrices
	free_matrix(4, 3, m1);
	free_matrix(3, 2, m2);

    // calculate the time elapsed for matrix with dimension ranging from 100 to 1000
    for(int i=100;i<=1000;i=i+25){
        matrix_benchmark(i);
	}
    // show the result upon completion
    printf("press enter to continue...\n");
    getchar();

	return 0;
}


