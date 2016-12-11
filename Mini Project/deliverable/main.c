/*
 * main.c

 *
 *  Created on: 2015Äê11ÔÂ19ÈÕ
 *      Author: Dawei
 */


#include<stdio.h>
#include<stdlib.h>
#include "DecisionTreeFunc.h"
#include<time.h>
#include<omp.h>
#include "matrix.h"

/*
 * @parameter kfold: how many fold cross-validation
 * @parameter m: all the data stored in the matrix
 * @parameter row: number of rows
 * @parameter column: number of columns
 *
 * @return: accuracy
 */
 double cross_validation(matrix m,int row,int column,int kfold){//cross-validation for decision tree
	double accuracy=0;
	matrix test; matrix train;int num;int n;int l;int row1;
	for(int j=0;j<kfold;j++){
		if(j<row % kfold){//allocate memory for test and training data matrices
			test=make_matrix(row/kfold+1,column);
			train=make_matrix(row-row/kfold-1,column);
			row1=row-row/kfold-1;
		}else{
			test=make_matrix(row/kfold,column);
			train=make_matrix(row-row/kfold,column);
			row1=row-row/kfold;
		}
		n=0;l=0;
		for(int i=0;i<row;i++){
			if(i % kfold==j){//assign data entries to respective matrix
				for(int k=0;k<column;k++){
					test[n][k]=m[i][k];
				}
				n++;
			}else{
				for(int k=0;k<column;k++){
					train[l][k]=m[i][k];
				}
				l++;
			}
		}
		struct node1* tree=make_tree();
		create_tree(train,tree,row1,column,0,1);
		if(j<row%kfold){//classify and calculate accuracy
			int count=0;
			for(int m=0;m<(row/kfold+1);m++){
				num= classify(tree, test[m],0);
				if(num==test[m][column-1]){
					count++;
				}
			}
			printf("%d fold accuracy is %f\n",j+1,(double)count/(row/kfold+1));
			accuracy+=(double) count/(row/kfold+1);
			free_matrix(row/kfold+1,column,test);
			free_matrix(row-row/kfold-1,column,train);
		}else{
			int count=0;
			for(int m=0;m<(row/kfold);m++){
				num= classify(tree, test[m],0);
				if(num==test[m][column-1]){
					count++;
				}
			}
			printf("%d fold accuracy is %f\n",j+1,(double)count/(row/kfold));
			accuracy+=(double) count/(row/kfold);
			free_matrix(row/kfold,column,test);
			free_matrix(row-row/kfold,column,train);
		}
		free_tree(tree);
	}

	return (double)accuracy/kfold;
}
 //ith fold validation for decision tree
double i_fold(matrix m,int row,int column,int kfold, int p){
	double accuracy;
	matrix test; matrix train;int num;int n;int l;int row1;

	if(p<row % kfold){//allocate memory for test and training data matrices
		test=make_matrix(row/kfold+1,column);
		train=make_matrix(row-row/kfold-1,column);
		row1=row-row/kfold-1;
	}else{
		test=make_matrix(row/kfold,column);
		train=make_matrix(row-row/kfold,column);
		row1=row-row/kfold;
	}
	n=0;l=0;
	for(int i=0;i<row;i++){
		if(i % kfold==p){//assign data entries to respective matrix
			for(int k=0;k<column;k++){
				test[n][k]=m[i][k];
			}
			n++;
		}else{
			for(int k=0;k<column;k++){
				train[l][k]=m[i][k];
			}
			l++;
		}
	}
	struct node1* tree=make_tree();

	//double start1 = omp_get_wtime();
	create_tree(train,tree,row1,column,0,1);
	//printf("Time elapsed to build the model=%.2f\n", omp_get_wtime()-start1); // print parallel time elapsed
	if(p<row%kfold){//classify and calculate accuracy
		int count=0;
		for(int m=0;m<(row/kfold+1);m++){
			num= classify(tree, test[m],0);
			if(num==test[m][column-1]){
				count++;
			}
		}
		accuracy=(double) count/(row/kfold+1);
		free_matrix(row/kfold+1,column,test);
		free_matrix(row-row/kfold-1,column,train);
	}else{
		int count=0;
		for(int m=0;m<(row/kfold);m++){
			num= classify(tree, test[m],0);
			if(num==test[m][column-1]){
				count++;
			}
		}
		accuracy=(double) count/(row/kfold);
		free_matrix(row/kfold,column,test);
		free_matrix(row-row/kfold,column,train);
		}
	free_tree(tree);

	return accuracy;
}
/*
 * @parameter kfold: how many fold cross-validation
 * @parameter m: all the data stored in the matrix
 * @parameter line: number of rows
 * @parameter column: number of columns
 * @usage: measure the performance of parallel computing using Openmp
 */

void benchmark(matrix m,int line, int column,int kfold,int numthread){
	int j=numthread;
	printf("%d fold cross validation with parallel(%d thread)(focus on time): \n",kfold,j);
	double accuracy2=0;
	double start1 = omp_get_wtime();
	omp_set_num_threads(j);
	#pragma omp parallel
	{
		int i, id, nthrds;
		int line1=line; int column1=column;
		matrix x=m; int kfold1=kfold; double acc;
		id=omp_get_thread_num();
		nthrds=omp_get_num_threads();
		for(i=id,acc=0;i<kfold1;i+=nthrds){
			acc+=i_fold(x,line1,column1,kfold1,i);
		}
		#pragma omp critical
		{
			accuracy2+=acc;
		}

	}
	printf("Time elapsed with parallel(%d thread)=%.2f\n", j,omp_get_wtime()-start1);  // print time elapsed

}

int main(int argc, const char * argv[]) {
	 if (argc != 2) {
	        return 0;
	    }
	const char* fname = argv[1];
	FILE *dataset=fopen(fname,"r");// read file
	if (dataset == NULL) {
		printf("Can't open input file!\n");
		exit(1);
	}
	unsigned line,column;
	fscanf(dataset,"%i,%i",&line,&column);// get number of rows and number of columns
	matrix m=ReadData(dataset,line,column);//read data into matrix m

	//measure performance
	double start; double acc=0;
	start=omp_get_wtime();
	printf("10-fold cross validation without parallel: \n");
	double accuracy=cross_validation(m,line,column,10);
	printf("10-fold average accuracy is %f:\n", accuracy);


	// measure time without parallel;
	printf("Time elapsed without parallel=%.2f\n", omp_get_wtime()-start);  // print time elapsed
/*
	// measure time with parallel;
	benchmark(m,line,column,10,10);

	//measure the relationship between time and number of folds
	for(int j=2;j<=10;j=j+2){
		benchmark(m,line,column,10,j);
	}
	for(int j=2;j<=10;j=j+2){
		benchmark(m,line,column,20,j);
	}*/
	free_matrix(line,column,m);
	return 0;
}



