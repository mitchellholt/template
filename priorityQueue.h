#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// type of the elements in the priorityQueue
struct element {
    void *obj;
    int priority;
};

struct element *element_init(int priority, void *obj);

// PriorityQueue type using heap implemented as an array
typedef struct {
    struct element **elements; // dynamic array of elements of the queue
    int maxCapacity; // the maximum elements to be stored in the array
    int length; // the number of elements currently stored. Note that 
                // length - 1 is the position of the last element
} PriorityQueue;

/*
 * Allocate storage for and return a pointer to a new PriorityQueue with the
 *  supplied maximum capacity, an empty (but initialised) array of elements,
 *  and initial length 0
 */
PriorityQueue *pq_init(int maxCapacity);

/*
 * Free all memory used by the given priority queue and its members, but not
 *  the memory used by the elements of the queue.
 */
void pq_free(PriorityQueue *pq);

/*
 * Add the given element to the given priority queue, updating the order if
 *  neccesary. If an element was removed from the heap (to keep the length less
 *  than the maximum capacity), return it. Otherwise, return NULL.
 */
struct element *pq_add(PriorityQueue *pq, struct element *item);

/*
 * Remove and return the minimum element of the priority queue and rebalance
 *  the queue. If the queue is empty, return NULL.
 */
struct element *pq_remove(PriorityQueue *pq);

#endif
