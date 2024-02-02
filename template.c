#include "template.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


// Prepend env variable TEMPLATE_PATH (otherwise default path) to filename,
// then attempt to open file.
char *make_template_name(const char *template_filename)
{
    if (!template_filename) return NULL;
    // Construct the path to the directory
    // make it a static variable for sizeof, good code quality I guess
    static const char default_template_directory[] = DEFAULT_TEMPLATE_DIRECTORY;
    char *templates_path;
    const char *env_path;
    unsigned long length = strlen(template_filename);
    if ((env_path = getenv(TEMPLATE_ENV)))
    {
        unsigned long num_env_bytes = strlen(env_path) + 1;
        templates_path = malloc(num_env_bytes + length);
        memcpy(templates_path, env_path, num_env_bytes);
    }
    else
    {
        templates_path = malloc(sizeof(default_template_directory) + length);
        memcpy(
                templates_path,
                default_template_directory,
                sizeof(default_template_directory));
    }

    return strcat(templates_path, template_filename);
}


// Copy the file and close the file pointers. Return 
enum Err copy_file(int from, int to)
{
    char buf[4096];
    ssize_t nread;
    while (nread = read(from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(to, out_ptr, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else
            {
                close(from);
                close(to);
                return SYS_ERR;
            }
        } while (nread > 0);
    }
    close(from);
    close(to);
    return SUCCESS;
}


DIR *open_template_directory()
{
    char *templates_path;
    if ((templates_path = getenv(TEMPLATE_ENV)))
    {
        return opendir(templates_path);
    }
    return opendir(DEFAULT_TEMPLATE_DIRECTORY);
}


const char *without_path(const char *filename)
{
    if (!filename) return NULL;
    const char *ptr = strrchr(filename, '/');
    return ptr ? ptr + 1 : filename;
}


enum Err new_template_file(const char *src_filename, const char *template_filename)
{
    int fd_from = open(src_filename, O_RDONLY);
    if (fd_from < 0) return DOES_NOT_EXIST;

    char *template_path = make_template_name(
            template_filename
                ? template_filename
                : without_path(src_filename));
    int fd_to = open(
            template_path,
            O_WRONLY | O_CREAT | O_EXCL,
            S_IRUSR | S_IWUSR);
    free(template_path);
    if (fd_to < 0)
    {
        close(fd_from);
        return DUPLICATE_NAME;
    }

    return copy_file(fd_from, fd_to);
}


enum Err from_template_file(const char *template_filename, const char *new_filename)
{
    char *template_path = make_template_name(template_filename);
    int fd_from = open(template_path, O_RDONLY);
    free(template_path);
    if (fd_from < 0) return DOES_NOT_EXIST;

    int fd_to = open(
            new_filename ? new_filename : template_filename,
            O_WRONLY | O_TRUNC | O_CREAT,
            S_IRUSR | S_IWUSR);
    if (fd_to < 0)
    {
        close(fd_from);
        return SYS_ERR;
    }

    return copy_file(fd_from, fd_to);
}


enum Err write_template_file(const char *template_filename, const char *src_filename)
{
    int fd_from = open(src_filename, O_RDONLY);
    if (fd_from < 0) return DOES_NOT_EXIST;

    char *template_path = make_template_name(template_filename);
    int fd_to = open(template_path, O_WRONLY | O_TRUNC);
    free(template_path);
    if (fd_to < 0)
    {
        close(fd_from);
        return DOES_NOT_EXIST;
    }

    return copy_file(fd_from, fd_to);
}


enum Err list_template_files(void)
{
    struct dirent *entry;
    DIR *dir = open_template_directory();
    if (!dir) return DOES_NOT_EXIST;
    while ((entry = readdir(dir)))
    {
        if (entry->d_type == DT_REG) printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return SUCCESS;
}
