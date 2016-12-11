/*
 * heap.c
 *
 *  Created on: 2015Äê10ÔÂ5ÈÕ
 *      Author: Dawei
 */



#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


struct heap {
	int size;
	int count;
	struct heap1 *heap1;

};
struct heap1{
		void *data;
	    double heaparr;
	};

int initial_size = 100;
//struct heap h[initial_size];
struct heap* pq_create(){
	struct heap *h = (struct heap *) malloc(sizeof(struct heap));
	h->heap1=(struct heap1*)malloc(sizeof(struct heap1)*initial_size);
	h->count = 0;
	h->size = initial_size;


	if(!h) {
			printf("Error allocating a memory...\n");
			exit(-1);
		}
	return h;
}
// define priority queue structure that
// holds the head node and the size

void pq_push(struct heap *h,double value,void *d){
	if(h->count==h->size){
		h->size+=1;
		h->heap1=realloc(h->heap1,sizeof(struct heap1)*h->size);
		if(!h->heap1) exit(-1);
	}
	h->count=h->count+1;
	h->heap1[h->count-1].heaparr=value;
	h->heap1[h->count-1].data=d;
	heapify_up(h,h->count-1);
}
void heapify_up(struct heap *h,int i){

	if(i==0){ return;}
	if(h->heap1[i].heaparr<h->heap1[(i-1)/2].heaparr){
		struct heap1 *temp=(struct heap1*)malloc(sizeof(struct heap1));
		*temp=h->heap1[i];
		h->heap1[i]=h->heap1[(i-1)/2];
		h->heap1[(i-1)/2]=*temp;
		heapify_up(h,(i-1)/2);

}else{
	return;
}
}
double pq_pop(struct heap *h){

	double d=h->heap1[0].heaparr;
	h->heap1[0]=h->heap1[h->count-1];
	h->count=h->count-1;
	if((h->count<h->size)&&(h->size>initial_size)){
		h->size=h->size-1;
		h->heap1=realloc(h->heap1,sizeof(struct heap1)*h->size);
		if(!h->heap1) exit(-1);
	}

	heapify_down(h,0);

	return d;
}

void heapify_down(struct heap *h,int i){
	struct heap1 *temp=(struct heap1*)malloc(sizeof(struct heap1));
	if((h->count-1)<2*i+1){
		return;
	}else if(((h->count-1)>=2*i+1) && ((h->count-1)<2*i+2)){
			if(h->heap1[i].heaparr > h->heap1[2*i+1].heaparr){
				*temp=h->heap1[2*i+1];
				h->heap1[2*i+1]=h->heap1[i];
				h->heap1[i]=*temp;
			}else{
				return;
			}
		}else{
			if(h->heap1[i].heaparr<h->heap1[2*i+1].heaparr && h->heap1[i].heaparr<h->heap1[2*i+2].heaparr){
					return;
				}else if(h->heap1[2*i+1].heaparr<h->heap1[2*i+2].heaparr){
					*temp=h->heap1[2*i+1];
					h->heap1[2*i+1]=h->heap1[i];
					h->heap1[i]=*temp;
					heapify_down(h,2*i+1);
				}else{
					*temp=h->heap1[2*i+2];
					h->heap1[2*i+2]=h->heap1[i];
					h->heap1[i]=*temp;
					heapify_down(h,2*i+2);
				}

		}
		free(temp);
	}

int pq_size(struct heap *h) {
    if (h == NULL)
        return 0;

    return h->count;
}

void pq_free(struct heap *h) {
	while(h->count != 0) {
	   pq_pop(h);
	}
}
