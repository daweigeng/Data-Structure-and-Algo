/*
 * data.h
 *
 *  Created on: 2015Äê11ÔÂ19ÈÕ
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
 * Print matrix for matrix of size n1*n2
 *
 * @param n1 the size of the row for matrix 1
 * @param n2 the size of the col for matrix 1
 * @param a is matrix we want to print
 * @return 0 if print succeeds; NULL if print fails
 */

void matrix_print(int n1, int n2, matrix a);
/*
 * read data into matrix
 *
 * @param line the size of the row
 * @param column the size of the col
 * @param dataset: File
 * @return matrix that stores the data
 */
matrix ReadData(FILE *dataset,unsigned line, unsigned column);


#endif /* MATRIX_H_ */
