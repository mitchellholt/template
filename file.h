// file.h
//
// Mitchell Holt, Jan 2023

#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdbool.h>

/*
 * Copy the file at existingPath to the current directory, renaming it to
 *  newName. If newName is NULL, assign it the name of the old file. Return true
 *  on success, or false if any system calls fail
 */
bool copy_file(char *existingPath, char *newName);

/* 
 * Return the next line from the given stream. If there is no more text to be
 *  read, return NULL. Otherwise return a pointer to the text read.
 */
char *read_line(FILE *stream);

#endif
