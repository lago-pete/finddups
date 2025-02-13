#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#ifndef FINDDUPS_H


#define FINDDUPS_H

typedef struct {
    char *path;
    int size;
    int paired;
} file_spec;


struct Node {
    file_spec data;
    struct Node* next;
};





int compareFiles(char *fname0, char *fname1);
void path(const char *path);
void file_proc(const char *filepath);
void direc(const char *dirpath);

#endif
