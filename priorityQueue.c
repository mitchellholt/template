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
    pq->elements = malloc(sizeof(void*) * (maxCapacity + 1));
    pq->length = 0;
    return pq;
}

/* parent()
 * --------------------------------
 * Given the index of an element in a heap, get index of the parent of that
 *  element
 *
 * thisIndex: The index of the element of which the index of the parent is to be
 *  found.
 *
 * Returns: The index of the parent of the element at thisIndex.
 */
int parent(int thisIndex) {
    if (!thisIndex) {
        return -1;
    }

    // find smallest n such that 2^n - 1 < thisIndex
    int n = 0;
    while ((2 << (n - 1)) - 1 < thisIndex) {
        n++;
    }

    int offset = thisIndex - ((2 << (n - 1)) - 1); // 2^n = 2 << (n - 1)
    
    return ((2 << (n - 2)) - 1) + (offset >> 1);
}

/* upheap()
 * -----------------------------------
 * Restore heap order, assuming all but the last element are in order.
 *
 * pq: The PriorityQueue in which to restore heap order.
 */
void upheap(PriorityQueue *pq) {
    // TODO
}

/* downheap()
 * -----------------------------------
 * Restore heap order, assuming all but the first element are in order.
 *
 * pq: The PriorityQueue in which to restore heap order.
 */
void downheap(PriorityQueue *pq) {
    // TODO
}

void pq_free(PriorityQueue *pq) {
    if (!pq) return;
    free(pq->elements);
    free(pq);
}

void *pq_add(PriorityQueue *pq, void *item) {
    pq->elements[pq->length++] = item;
    
    upheap(pq);

    if (pq->length > pq->maxCapacity) {
        pq->length--;
        return pq->elements[pq->length];
    }

    return NULL;
}

void *pq_remove(PriorityQueue *pq) {
    if (!pq->length) {
        return NULL;
    }

    void *result = pq->elements[0];

    pq->elements[0] = pq->elements[pq->length - 1];
    pq->length--;

    downheap(pq);

    return result;
}
