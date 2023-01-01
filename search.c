// search.c
//
// Mitchell Holt, Dec 2022
//
// Functions to saerch the template directory for results and return them

#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "priorityQueue.h"

#define REPLACEMENT_WEIGHT 2
#define INSERTION_WEIGHT 1
#define DELETION_WEIGHT 1

char *get_templates_path(Params *params) {
    if (params->templatesPath) return params->templatesPath;

    char *path = getenv(TEMPLATE_DIRECTORY_PATH);
    if (path) return path;

    return DEFAULT_DIRECTORY_PATH;
}

/*
 *
 */
int minimum(int count, int values[]) {
    int min = 0;
    if (count) {
        min = values[0];
    } else {
        return min;
    }

    for (int i = 0; i < count; i++) {
        if (values[i] < min) {
            min = values[i];
        }
    }

    return min;
}

// Wagner-Fischer Algorithm
int search_distance(const char *filename, const char *query) {
    // initialise distances matrix
    int m = strlen(filename) + 1;
    int n = strlen(query) + 1;
    int **d = malloc(sizeof(int*) * m);
    for (int i = 0; i < m; i++) {
        d[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            if (!i) {
                d[i][j] = j;
            } else if (!j) {
                d[i][j] = i;
            } else {
                d[i][j] = 0;
            }
        }
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            int substitutionCost = (filename[i] == query[j])
                ? 0
                : 1;
            int values[] = {
                d[i - 1][j] + 1,
                d[i][j - 1] + 1,
                d[i - 1][j - 1] + substitutionCost
            };
            d[i][j] = minimum(3, values);
        }
    }

    int result = d[m][n];

    for (int i = 0; i < m; i++) {
        free(d[i]);
    }
    free(d);

    return result;
}

// TODO implement extension stuff
char **search(DIR *path, const char *query, bool extension) {
    struct dirent *entry;
    PriorityQueue *pq = pq_init(5);

    while ((entry = readdir(path))) { // NOTE: do NOT free entry (see man page)
        if (entry->d_type != DT_REG) continue;
        int distance = search_distance(entry->d_name, query);
        struct element *result = element_init(distance, entry->d_name);
        struct element *removed = pq_add(pq, result);
        if (removed) {
            element_clean(removed);
        }
    }

    struct element *removed;
    char **results = NULL;
    int resultsCount = 0;
    while ((removed = pq_remove(pq))) {
        results = realloc(results, sizeof(char*) * (resultsCount + 1));
        char *name = malloc(sizeof(char) * (strlen(removed->obj) + 1));
        strcpy(name, removed->obj);
        element_clean(removed);
        results[resultsCount++] = name;
    }

    pq_free(pq);

    results = realloc(results, sizeof(char*) * (resultsCount + 1));
    results[resultsCount] = NULL;

    return results;
}
