// template.c
//
// Mitchell Holt, Dec 2022

#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include <ctype.h>
#include "file.h"

#define MAX_SEARCH_RESULTS 5

Params *params_init(void) {
    Params *params = malloc(sizeof(Params));
    params->extension = false;
    params->templatesPath = NULL;
    params->newName = NULL;
    params->query = NULL;
    return params;
}

void params_clean(Params *params) {
    free(params->templatesPath);
    free(params->newName);
    free(params->query);
    free(params);
}

/*
 * Read a line from the given stream. If EOF is reached before any characters
 *  can be read, return NULL.
 */
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr,
            "Usage: template new_name template_name [directory_path]\n");
        return 1;
    }

    Params *params = params_init();

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "-extension")) {
            params->extension = true;
        } else if (!params->newName) {
            params->newName = malloc(sizeof(char) * (strlen(argv[i]) + 1));
            strcpy(params->newName, argv[i]);
        } else if (!params->query) {
            params->query = malloc(sizeof(char) * (strlen(argv[i]) + 1));
            strcpy(params->query, argv[i]);
        } else if (!params->templatesPath) {
            params->templatesPath = malloc(sizeof(char) * (strlen(argv[i]) + 1));
            strcpy(params->templatesPath, argv[i]);
        } else {
            fprintf(stderr,
                "Usage: template new_name template_name [directory_path]\n");
            return 1;
        }
    }

    char *directory_path = get_templates_path(params);
    DIR *dir = opendir(directory_path);
    if (!dir) {
        perror("Cannot open template directory");
        return 2;
    }

    char **results = search(dir, params->query, params->extension);
    char *selectedFile = NULL;
    while (!selectedFile) {
        // print all results (type definition in search.h) to the screen, then read
        // user input.
        printf("Please number to select a template, or enter a new search "
                "term\n");
        int numResults = 0;
        for (; results[numResults]; numResults++) {
            printf("(%i)  %s\n", numResults + 1, results[numResults]);
        }

        char *input = read_line(stdin);
        if (isdigit(input[0]) && !input[1]) {
            int selectedNum = atoi(input);
            if (selectedNum < 1 || selectedNum > numResults) continue;
            selectedFile =
                malloc(sizeof(char) * (strlen(results[selectedNum]) + 1));
            strcpy(selectedFile, results[selectedNum]);
            free(input);
        } else {
            for (int i = 0; results[i]; i++) {
                free(results[i]);
            }
            free(results);
            results = search(dir, input, params->extension);
        }
        free(input);
    }

    params_clean(params);
    
    for (int i = 0; results[i]; i++) {
        free(results[i]);
    }
    free(results);
    closedir(dir);

    directory_path = realloc(params->templatesPath,
            sizeof(char) *
                (strlen(directory_path) + strlen(selectedFile) + 2));
    if (params->templatesPath[strlen(directory_path) - 1] != '/') {
        strcat(directory_path, "/");
    }
    strcat(directory_path, selectedFile);

    char *copied = copy_file(directory_path, params->newName);

    if (copied) {
        fprintf(stderr, "Could not copy template: %s\n", copied);
        return 1;
    }

    return 0;
}
