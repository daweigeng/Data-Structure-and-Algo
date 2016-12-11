Matrix Library Instructions on Jinx:
1. I have already uploaded in my file within jinx cluster, you should be able to see three files in my file, which are matrix.c, matrix.h,matrix_test.c.
2. type in ls in the command line of jinx to see if these three files are in there.
3. using command gcc -I -q class -l nodes=1 -l walltime=00:05:00 to log you into the home directory of a compute node.
4. To compile, type in gcc matrix.c matrix_test.c -std=c99 -o myprog
5. ./prog to run the executable file, and then you will see the result of the program.

In this zip file, you will see three files: 
1.Release, which includes the software; 
2.Source code, which includes C code; 
3.Q7 Plot, which includes brief report of the plot, Matlab prog, and the plot.

If you run the code, you will find the code will 
1.assign computer memory for matrix
2.randomly generate two matrices;
3.do matrix multiplication;
4.time the multiplication;
5.print the product;
6.free the assigned memory.
7.benchmark function to time the matrix multiplication with different dimension 

