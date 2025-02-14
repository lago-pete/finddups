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


typedef struct Node{
    file_spec data;
    struct Node* next;
} Node;



Node* createNode(file_spec datas);
void insert(Node** head, file_spec datas);
Node** resizeArray(Node** lists, int* current_size, int* max_size);
void print_lists(Node** lists, int current_size, int num_of_items);
int hash_function(off_t size, int max_size);


int compareFiles(char *fname0, char *fname1);
void path(const char *path, Node** lists, int* current_size, int* max_size, int* num_of_files);
void file_proc(const char *filepath, Node** lists, int* current_size, int* max_size, int* num_of_files);
void direc(const char *dirpath, Node** lists, int* current_size, int* max_size,  int* num_of_files);

#endif
