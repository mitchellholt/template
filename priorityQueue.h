#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// PriorityQueue type using heap implemented as an array
typedef struct {
    void **elements; // dynamic array of elements of the queue
    int maxCapacity; // the maximum elements to be stored in the array
    int length; // the number of elements currently stored. Note that 
                // length - 1 is the position of the last element
} PriorityQueue;

/* pq_init()
 * ----------------------------
 * Allocate storage for and return a new PriorityQueue with the supplied maximum
 *  capacity, an empty (but initialised) array of elements, and initial length 0
 *
 * maxCapacity: the maximum capacity for the PriorityQueue to be created
 *
 * Returns: A new PriorityQueue.
 */
PriorityQueue *pq_init(int maxCapacity);

/* pq_free()
 * ------------------------------------
 * Free all memory used by the given priority queue and its members, but do Note
 *  free the memory used by the elements of the queue.
 *
 * pq: The priority queue to be freed.
 */
void pq_free(PriorityQueue *pq);

/* pq_add()
 * --------------------------------------
 * Add the given element to the given priority queue, updating the order if
 *  neccesary. If an element was removed from the heap (to keep the length less
 *  than the maximum capacity), return it.
 *
 * pq: The priority queue into which the new element is to be inserted
 * item: The item to be inserted
 *
 * Returns: If no item was removed from the queue to keep the length bounded,
 *  return NULL. Otherwise return the item that was removed.
 */
void *pq_add(PriorityQueue *pq, void *item);

/* pq_remove()
 * -----------------------------------
 * Remove the minimum element of the priority queue and rebalance the queue.
 *
 * pq: The priority queue from which to remove the minimum element
 *
 * Returns: NULL if pq is empty, otherwise the minimum element.
 */
void *pq_remove(PriorityQueue *pq);

#endif
