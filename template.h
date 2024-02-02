#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#define DEFAULT_TEMPLATE_DIRECTORY "~/Documents/Templates/"
#define TEMPLATE_ENV "TEMPLATE_PATH"

enum Err
{
    SUCCESS,
    DOES_NOT_EXIST,
    DUPLICATE_NAME,
    SYS_ERR
};

enum Err new_template_file(const char *source_filename, const char *template_filename);

enum Err from_template_file(const char *template_filename,
        const char *new_filename);

enum Err write_template_file(const char *tempate_filename,
        const char *src_filename);

enum Err list_template_files(void);

#endif
