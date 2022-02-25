#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "file.h"

struct file *file_constructor(const char *filename)
{
    size_t pagesize = (size_t) sysconf(_SC_PAGESIZE);
    struct stat tmp;
    struct file *new = calloc(1, sizeof (struct file));
    if (new == NULL)
        return NULL;

    new->fd = open(filename, 0400);
    if (new->fd == -1)
    {
        fprintf(stderr, "Cannot open %s file in read-only mode.\n", filename);
        free(new);
        return NULL;
    }

    stat(filename, &tmp);
    new->filesize = tmp.st_size;

    new->memory = mmap(0, new->filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, new->fd, 0);
    if (new->memory == NULL)
    {
        fprintf(stderr, "Impossible to allocate enough memory pages.\n");
        free(new);
        return NULL;
    }

    while (new->pagesize < new->filesize)
        new->pagesize += pagesize;

    new->memory[new->filesize - 1] = '\0';

    return new;
}


void file_destructor(struct file **f)
{
    close((*f)->fd);
    munmap((*f)->memory, (*f)->pagesize);
    free(*f);
    *f = NULL;
}
