#ifndef SEARCH_H

#define SEARCH_H

/* get_template_path()
 * ----------------------------
 * Get the path to the template directory
 *
 * override: The argument passed to the -dir flag (if it was used), otherwise
 *  NULL
 * 
 * Returns: A string representation of the path to the templates directory.
 */
char *get_template_path(const char *override);

// Struct containing a number-result map from the search function
typedef struct {
    int num; // the unique number assigned to this result
    char *name; // the file name
} SearchResults;

/* search()
 * ----------------------------
 * Search the given path and return the five (if there are at least five files
 *  at the location) closest results (in order) to the query. The extension flag
 *  determines if "file.extension" is considered a match only if extension
 *  matches the one (if any) in the query.
 *
 * path: The path to the directory to be searched
 * query: The search term
 * extension: The flag determining if extensions are to be considered.
 */
SearchResults *search(const char *path, const char *query, bool extension);

#endif
