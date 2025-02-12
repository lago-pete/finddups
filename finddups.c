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
    if (stat(filepath, &file_stat) == -1) {
        fprintf(stderr, "Error statting file: %s\n", filepath);
        return;
    }
    


    
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