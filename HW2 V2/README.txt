Priority queue with heap Instructions on Jinx:
1. I have already uploaded in my file within jinx cluster, you should be able to see three files in my file, which are main.c, heap.h,heap.c.
2. type in ls in the command line of jinx to see if these three files are in there.
3. using command gcc -I -q class -l nodes=1 -l walltime=00:05:00 to log you into the home directory of a compute node.
4. To compile, type in gcc main.c heap.c -std=c99 -o myprog
5. ./prog to run the executable file, and then you will see the result of the program.

Comment: Dawei Geng developed for the first question of version 2, which is to create the priority queue, test it, and draw some conclusion based on that.
Tse-wei Fu developed for the second question of version 2, which is to model aircraft departure.

Dawei Geng includes two source codes, one is Test program code(in Test program directory) including test for the heap structure and test for the double linked list structure, the other code(in the "Simulation Engine 1st part" directory) is the simulation engine using heap.
Tse-Wei Fu includes a source code of simulation engine he developed in the "Simulation Engine 2nd part" Directory. 