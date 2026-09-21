#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <sys/types.h>
#include <sys/stat.h>

int open_file(const char *filename);
int get_file_size(int fd, struct stat *file_info);
int close_file(int fd);

#endif
