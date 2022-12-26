// search.c
//
// Mitchell Holt, Dec 2022
//
// Functions to saerch the template directory for results and return them

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include "search.h"
#include "priorityQueue.h"

#define REPLACEMENT_WEIGHT 2
#define INSERTION_WEIGHT 1
#define DELETION_WEIGHT 1

// type of the elements in the priorityQueue
struct element {
    char *filename;
    int distance;
};

char *get_templates_path(Params *params) {
    if (params->templatesPath) {
        return params->templatesPath;
    }

    char *path = getenv(TEMPLATE_DIRECTORY_PATH);
    if (path) {
        return path;
    }

    return DEFAULT_DIRECTORY_PATH;
}

// TODO
SearchResults *search(DIR *path, const char *query, bool extension) {
    struct dirent *entry;
    PriorityQueue *results = pq_init(5);

    while ((entry = readdir(path))) {

    }

    return NULL;
}
