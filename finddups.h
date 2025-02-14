#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

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



struct Node* createNode(file_spec datas);
void insert(struct Node** head, file_spec datas);
struct Node** resizeArray(struct Node** lists, int* current_size, int* max_size);
void print_lists(struct Node** lists, int current_size);
int hash_function(off_t size, int max_size);


int compareFiles(char *fname0, char *fname1);
void path(const char *path, struct Node** lists, int* current_size, int* max_size, int* num_of_files);
void file_proc(const char *filepath, struct Node** lists, int* current_size, int* max_size, int* num_of_files);
void direc(const char *dirpath, struct Node** lists, int* current_size, int* max_size,  int* num_of_files);

#endif
