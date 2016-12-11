/*
 * heap.h
 *
 *  Created on: 2015Äê10ÔÂ7ÈÕ
 *      Author: Dawei
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <stdio.h>
typedef struct heap heap;
/*
 * Create an empty priority queue.
 *
 * @return a pointer to the priority queue.
 */
struct heap* pq_create();
/*
 * Push an element with a given priority into the queue.
 *
 * @param h the priority queue
 * @param value the element's priority
 * @param d the data representing our element
 */
void pq_push(struct heap *h,double value,void *d);

void heapify_up(struct heap *h,int i);
/*
 * Pop the top element from the priority queue.
 *
 * @param pq the priority queue
 *
 * @return the timestamp representing the top element
 */
double pq_pop(struct heap *h);

void heapify_down(struct heap *h,int i);
/*
 * Get the size of the priority queue
 *
 * @param pq the priority queue
 *
 * @return the size of the queue
 */
int pq_size(struct heap *h);
/*
 * Free the memory allocated to the priority queue.
 *
 * @param pq the priority queue
 */
void pq_free(struct heap *h);

#endif /* HEAP_H_ */
