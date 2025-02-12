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
    char *file_name;
    char *path;
    int size;
} file_spec;

typedef struct {
    file_spec *files; 
    int count;    
    int capacity;  
} bucket;

typedef struct {
    int size;        
    bucket *buckets; 
} table;






int compareFiles(char *fname0, char *fname1);
void path(const char *path);
void file_proc(const char *filepath);
void direc(const char *dirpath);

#endif
