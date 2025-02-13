#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "finddups.h"

#define MAX_PATH 4096


void path(const char *path) {
    struct stat path_stat;
   
    stat(path, &path_stat);

    if (S_ISREG(path_stat.st_mode)) {
        file_proc(path);  
    } else if (S_ISDIR(path_stat.st_mode)) {
        direc(path);
    } else {
        fprintf(stderr, "Ignoring non-regular file: %s\n", path);
    }
}


void file_proc(const char *filepath) {
    //printf("Processing file: %s\n", filepath);
    struct stat file_stat;
    stat(filepath, &file_stat);

    file_spec *file_s;

    file_s->path = filepath;
    file_s->size = file_stat.st_size;
    file_s->paired = 0;


    
    

    
}


void direc(const char *dirpath) {
    //printf("Processing directory: %s\n", dirpath);
    DIR *dir = opendir(dirpath);

    struct dirent *input;
    char full_path[MAX_PATH];

    while ((input = readdir(dir)) != NULL) {
        
        if (strcmp(input->d_name, ".") == 0 || strcmp(input->d_name, "..") == 0) {     //this line was basically copied from geeks for geeks its just formating though
            continue;
        }

        snprintf(full_path, MAX_PATH, "%s/%s", dirpath, input->d_name);
        path(full_path);
    }

    closedir(dir);
}









int compareFiles(char *fname0, char *fname1)
{
    int ch0, ch1;
    FILE *file0 = fopen(fname0, "r");
    FILE *file1 = fopen(fname1, "r");

    if (file0 == NULL || file1 == NULL)
    {
        eprintf_fail("Error Opening FILE");

        return 0;
    };

    while (1)
    {
        ch0 = getc(file0);
        ch1 = getc(file1);

        if (ch0 == EOF && ch1 == EOF)
        {
            return 1;
        }

        if (ch0 != ch1)
        {
            return 0;
        }
    }
    eprintf("Passed");
    return 1;
}






// Function to create a new node
struct Node* createNode(file_spec datas) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));

    new->data = datas;
    new->next = NULL;
    return new;
}


void insert(struct Node** head, file_spec datas) {
    struct Node* newNode = createNode(datas);
    newNode->next = *head;
    *head = newNode;
}



struct Node** resizeArray(struct Node** lists, int* current_size) {
    int new = (*current_size) * 2; 
    struct Node** newLists = (struct Node**)realloc(lists, new * sizeof(struct Node*));
    
    for (int i = *current_size; i < new; i++) {
        newLists[i] = NULL;
    }

    *current_size = new;
    return newLists;
}










