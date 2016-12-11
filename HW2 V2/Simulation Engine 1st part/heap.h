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
struct heap* heap_init();
void heap_insert(struct heap *h,double value,void *d);
void heapify_up(struct heap *h,int i);
void* heap_delete(struct heap *h);
void heapify_down(struct heap *h,int i);
int heap_size(struct heap *h);
void empty_heap(struct heap *h);

#endif /* HEAP_H_ */
