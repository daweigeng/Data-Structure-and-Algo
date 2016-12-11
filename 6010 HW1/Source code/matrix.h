/*
 * matrix.h
 *
 *  Created on: 2015Äê8ÔÂ31ÈÕ
 *      Author: Dawei
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include<stdio.h>

typedef double** matrix; //matrix type is array of pointers pointing to array of elements of type double
/*
 * Allocate space for a matrix of size n1*n2
 *
 * @param n1 the size of the allocated row for matrix
 * @param n2 the size of the allocated col for matrix
 * @return the allocated matrix; NULL if allocation fails
 */
matrix make_matrix(int n1, int n2);
/*
 * Free space for a matrix of size n1*n2
 *
 * @param n1 the size of the row for matrix
 * @param n2 the size of the col for matrix
 * @param a the matrix we want to free
 * @return 0 if free succeeds; NULL if free fails
 */
int free_matrix(int n1, int n2, matrix a);
/*
 * Matrix Multiplication for matrix 1 of size n1*n2 and matrix 2 of size n2*n3
 *
 * @param n1 the size of the row for matrix 1
 * @param n2 the size of the col for matrix 1 and the size of the row for matrix 2
 * @param n3 the size of the col for matrix 2
 * @param a is matrix 1
 * @param b is matrix 2
 * @param c is the product we got from the multiplication
 * @return 0 if multiplication succeeds; NULL if multiplication fails
 */
int matrix_multiply(int n1, int n2, int n3, matrix a, matrix b, matrix c);
/*
 * Matrix filled randomly for matrix of size n1*n2
 *
 * @param n1 the size of the row for matrix 1
 * @param n2 the size of the col for matrix 1
 * @param a is matrix we want to fill in randomly
 * @return 0 if matrix being filled in succeeds; NULL if matrix being filled in fails
 */
int matrix_fill_random(int n1,int n2, matrix a);
/*
 * Print matrix for matrix of size n1*n2
 *
 * @param n1 the size of the row for matrix 1
 * @param n2 the size of the col for matrix 1
 * @param a is matrix we want to print
 * @return 0 if print succeeds; NULL if print fails
 */

int matrix_print(int n1, int n2, matrix a);
/*
 * calculate the time for matrix multiplication with dimension n
 *
 * @param n is the dimension of matrix
 * @return 0 if benchmark succeeds; NULL if benchmark fails
 */
int matrix_benchmark(int n);

#endif /* MATRIX_H_ */
