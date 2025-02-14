#include "finddups.h"






int main(int argc, char *argv[]) {
    int max_size = 5;
    int num_of_files = 0;
    int current_size = 0;
    struct Node** lists = (struct Node**)malloc(size * sizeof(struct Node*));
    struct stat path_stat;
    stat(argv[1], &path_stat);




    for (int i = 0; i < size; i++) {
        lists[i] = NULL;
    }


    // Thought process: if there is no argument, then we will process the cwd.
    // Or if there is one argument which is a file, we will process that argument then the cwd.
    // But if there is only one argument and it is a directory then traverse just that directory and not the cwd. 
    if (argc < 2) {
        if(S_ISREG(path_stat.st_mode)) {
            file_proc(argv[1], lists, &current_size, &max_size, &num_of_files);
            path(".", lists, &current_size, &size, &num_of_files);
        }
        else if (S_ISDIR(path_stat.st_mode)) {
            path(argv[1], lists, &current_size, &max_size, &num_of_files);
        } 
        else{
            fprintf(stderr, "Ignoring non-regular file: %s\n", argv[1]);
            path(".", lists, &current_size, &max_size, &num_of_files);
        }
        
    } else {
        for (int i = 1; i < argc; i++) {
            path(argv[i], lists, &current_size, &max_size, &num_of_files);
        }
    }



    print_lists(lists, size);








    


    return 0;
}

