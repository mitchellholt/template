#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

struct element {
    char *filename;
    int distance;
};

typedef struct {
    struct element **elements;
    int maxCapacity;
    int length;
} PriorityQueue;

PriorityQueue *pq_init(int maxCapacity);

void pq_free(PriorityQueue *pq);

void pq_add(PriorityQueue *pq, struct element *item);

struct element *pq_remove(PriorityQueue *pq);

#endif
