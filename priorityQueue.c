// priorityQueue.c
//
// Written by Mitchell Holt
//
// API for priority queue

#include <stdlib.h>
#include "priorityQueue.h"

struct element *element_init(int priority, void *obj) {
    struct element *elem = malloc(sizeof(struct element));
    elem->priority = priority;
    elem->obj = obj;
    return elem;
}

void element_clean(struct element *elem) {
    free(elem);
}

PriorityQueue *pq_init(int maxCapacity) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->maxCapacity = maxCapacity;
    pq->elements = malloc(sizeof(struct element*) * (maxCapacity + 1));
    pq->length = 0;
    return pq;
}

/*
 * Find the largest integer k such that 2^k < n
 */
int greatest_power(int n) {
    int res = 0;
    while ((2 << (res - 1)) - 1 < n) {
        res++;
    }
    return res + 1;
}

/* 
 * Given the index of an element in a heap, get the index of the parent of that
 *  element
 */
int parent(int thisIndex) {
    if (!thisIndex) return -1;
    int n = greatest_power(thisIndex);
    int offset = thisIndex - ((2 << (n - 1)) - 1); // 2^n = 2 << (n - 1)
    return ((2 << (n - 2)) - 1) + (offset >> 1);
}


/*
 * Given the index of an element in a heap, get the index of the first child of
 *  the element. Note that a result will be returned even in the given element
 *  has no children. Always check that the result is less than the number of
 *  elements in the heap.
 */
int first_child(int thisIndex) {
    int n = greatest_power(thisIndex);
    int offset = thisIndex - n;
    return ((2 << (n + 1)) - 1) + (offset << 1);
}

/*
 * Starting from the last element, restore heap order lazily (assuming all but
 *  the last element are in order).
 */
void upheap(PriorityQueue *pq) {
    if (pq->length <= 1) return;
    int thisIndex = pq->length - 1;
    int parentIndex = parent(thisIndex);

    while (pq->elements[thisIndex]->priority
            < pq->elements[parentIndex]->priority) {
        // swap this and parent
        struct element *oldParent = pq->elements[parentIndex];
        pq->elements[parentIndex] = pq->elements[thisIndex];
        pq->elements[thisIndex] = oldParent;

        thisIndex = parentIndex;
        if (!thisIndex) return;
        parentIndex = parent(thisIndex);
    }
}

/*
 * Starting from the top, restore heap order lazily (assuming all but the first
 *  element are in order).
 */
void downheap(PriorityQueue *pq) {
    if (pq->length <= 1) return;
    int thisIndex = 0;
    int firstChildIndex = first_child(thisIndex);
    if (firstChildIndex >= pq->length) return;
    int minChildIndex =
        (firstChildIndex + 1 >= pq->length
            || pq->elements[firstChildIndex]->priority
                < pq->elements[firstChildIndex + 1]->priority)
        ? firstChildIndex
        : firstChildIndex + 1;
    
    while (pq->elements[thisIndex]->priority
            < pq->elements[minChildIndex]->priority) {
        // swap this and min child
        struct element *oldChild = pq->elements[minChildIndex];
        pq->elements[minChildIndex] = pq->elements[thisIndex];
        pq->elements[thisIndex] = oldChild;

        thisIndex = minChildIndex;
        firstChildIndex = first_child(thisIndex);
        if (firstChildIndex >= pq->length) return;
        minChildIndex =
            (firstChildIndex + 1 >= pq->length
                || pq->elements[firstChildIndex]->priority
                    < pq->elements[firstChildIndex + 1]->priority)
            ? firstChildIndex
            : firstChildIndex + 1;
    }
}

void pq_free(PriorityQueue *pq) {
    if (!pq) return;
    free(pq->elements);
    free(pq);
}

struct element *pq_add(PriorityQueue *pq, struct element *item) {
    pq->elements[pq->length++] = item;
    
    upheap(pq);

    if (pq->length > pq->maxCapacity) {
        pq->length--;
        return pq->elements[pq->length];
    }

    return NULL;
}

struct element *pq_remove(PriorityQueue *pq) {
    if (!pq->length) return NULL;

    struct element *result = pq->elements[0];

    pq->elements[0] = pq->elements[pq->length - 1];
    pq->length--;

    downheap(pq);

    return result;
}
