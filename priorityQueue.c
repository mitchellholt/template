// priorityQueue.c
//
// Written by Mitchell Holt
//
// API for priority queue

#include <stdlib.h>
#include "priorityQueue.h"

PriorityQueue *pq_init(int maxCapacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->maxCapacity = maxCapacity;
    pq->elements = malloc(sizeof(struct element*));
    pq->elements[0] = NULL;
    pq->length = 0;
    return pq;
}

void pq_free(PriorityQueue *pq) {
    if (!pq) return;

    if (pq->elements) {
        for (int i = 0; pq->elements[i]; i++) {
            free(pq->elements[i]);
        }
        free(pq->elements);
    }

    free(pq);
}

void pq_add(PriorityQueue *pq, struct element *item) {

}

struct element *pq_remove(PriorityQueue *pq) {

}
