#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_USAGE_ERR 1
#define ERR_MSG "Usage: template cmd src [dest]"
#define DEST_REQUIRED_MSG "Destination is required for write"
#define SRC_REQUIRED_MSG "Source file is required"

#define CMD_INDEX 1
#define TEMPLATE_FILE_INDEX 2
#define LOCAL_FILE_INDEX 3

// write to new template. dest filename is optional
#define NEW_STRING "new"
// create a new file from template
#define FROM_STRING "from"
// write to existing template
#define WRITE_STRING "write"
// list all template files
#define LIST_STRING "ls"


int main(int argc, char **argv)
{
    enum Err err;
    // Parse cmd line args and call lib functions.
    if (argc < CMD_INDEX + 1 || argc > LOCAL_FILE_INDEX + 1)
    {
        fprintf(stderr, "%s\n", ERR_MSG);
        exit(EXIT_USAGE_ERR);
    }

    if (!strcmp(argv[CMD_INDEX], NEW_STRING))
    {
        if (argc != 3)
        {
            fprintf(stderr, "%s\n", SRC_REQUIRED_MSG);
            exit(EXIT_USAGE_ERR);
        }
        err = new_template_file(argv[TEMPLATE_FILE_INDEX], argv[LOCAL_FILE_INDEX]);
    }
    else if (!strcmp(argv[CMD_INDEX], FROM_STRING))
    {
        if (argc < 3)
        {
            fprintf(stderr, "%s\n", SRC_REQUIRED_MSG);
            exit(EXIT_USAGE_ERR);
        }
        err = from_template_file(argv[TEMPLATE_FILE_INDEX], argv[LOCAL_FILE_INDEX]);
    }
    else if (!strcmp(argv[CMD_INDEX], WRITE_STRING))
    {
        if (argc != 4)
        {
            fprintf(stderr, "%s\n", DEST_REQUIRED_MSG);
            exit(EXIT_USAGE_ERR);
        }
        err = write_template_file(argv[TEMPLATE_FILE_INDEX], argv[LOCAL_FILE_INDEX]);
    }
    else if (!strcmp(argv[CMD_INDEX], LIST_STRING))
    {
        err = list_template_files();
    }
    else
    {
        fprintf(stderr, "Invalid command: %s\n", argv[CMD_INDEX]);
        exit(EXIT_USAGE_ERR);
    }

    switch (err)
    {
        case SUCCESS:
            break;
        case DOES_NOT_EXIST:
            fprintf(stderr, "%s\n", "Could not find template");
            break;
        case DUPLICATE_NAME:
            fprintf(stderr, "%s\n", "Duplicate file name");
            break;
        case SYS_ERR:
            fprintf(stderr, "%s\n", "IO error");
    }
    exit(EXIT_SUCCESS);
}
