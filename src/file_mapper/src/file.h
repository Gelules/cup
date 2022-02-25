#ifndef FILE_H
#define FILE_H

struct file
{
    int fd;
    size_t filesize;
    size_t pagesize;
    char *memory;
};

struct file *file_constructor(const char *filename);
void file_destructor(struct file **f);

#endif /* !FILE_H */
