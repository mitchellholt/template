// template.c
//
// Mitchell Holt, Dec 2022

#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"

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

    if (!params->query) {
        fprintf(stderr,
            "Usage: template new_name template_name [directory_path]\n");
        return 1;
    }

    char *directory_path = get_templates_path(params);
    DIR *dir;
    if (!(dir = opendir(directory_path))) {
        fprintf(stderr, "Cannot find directory %s\n", directory_path);
        return 2;
    }

    SearchResults *results = search(dir, params->query, params->extension);
}
