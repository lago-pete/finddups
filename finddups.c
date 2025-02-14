#include "finddups.h"
#define MAX_PATH 4096






void path(const char *path, Node** lists, int* current_size, int* max_size, int* num_of_files)
 {
    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISREG(path_stat.st_mode)) {
        file_proc(path, lists, current_size, max_size, num_of_files);  
    } else if (S_ISDIR(path_stat.st_mode)) {
        direc(path, lists, current_size, max_size, num_of_files);
    } else {
        fprintf(stderr, "Ignoring non-regular file: %s\n", path);
    }


}


void file_proc(const char *filepath, Node** lists, int* current_size, int* max_size, int* num_of_files)
 {
    //printf("Processing file: %s\n", filepath);
    struct stat file_stat;
    stat(filepath, &file_stat);

    file_spec *file_s = (file_spec*)malloc(sizeof(file_spec)); 

    file_s->path = strdup(filepath); // dont wont pointer errors, when implememnt first round of testing check for this
    file_s->size = file_stat.st_size;
    file_s->paired = 0;


    if (((float)(*current_size) / *max_size) > 0.75) {
        lists = resizeArray(lists, current_size, max_size);
    }

    
    int index = hash_function(file_s->size, *max_size);

    
    insert(&lists[index], *file_s);
    (*num_of_files)++;
    (*current_size)++; 
    

    
}


void direc(const char *dirpath, Node** lists, int* current_size, int* max_size, int* num_of_files)
{
    //printf("Processing directory: %s\n", dirpath);
    DIR *dir = opendir(dirpath);


    struct dirent *input;
    char full_path[MAX_PATH];

    while ((input = readdir(dir)) != NULL) {
                                                                                     //https://www.geeksforgeeks.org/snprintf-c-library/
        if (strcmp(input->d_name, ".") == 0 || strcmp(input->d_name, "..") == 0) {     //this line was basically copied from geeks for geeks its just formating though
            continue;
        }

        snprintf(full_path, MAX_PATH, "%s/%s", dirpath, input->d_name);

        path(full_path, lists, current_size, max_size, num_of_files);
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
        fclose(file0);
        fclose(file1);
        printf("Error: File not found\n");

        return 0;
    };

    while (1)
    {
        ch0 = getc(file0);
        ch1 = getc(file1);

        if (ch0 == EOF && ch1 == EOF)
        {
            fclose(file0);
            fclose(file1);
            return 1;
        }

        if (ch0 != ch1)
        {
            fclose(file0);
            fclose(file1);
            return 0;
        }
    }
        
    return 1;
}






// Function to create a new node
Node* createNode(file_spec datas) {
    Node* new = (Node*)malloc(sizeof(Node));

    new->data = datas;
    new->next = NULL;
    return new;
}


void insert(Node** head, file_spec datas) {
    Node* new = createNode(datas);
    new->next = *head;
    *head = new;
}



Node** resizeArray(Node** lists, int* current_size, int* max_size) {
    int new = (*max_size) * 2;
    Node** newLists = (Node**)malloc(new * sizeof(Node*));
   

    for (int i = 0; i < new; i++) {
        newLists[i] = NULL;
    }
    

    for (int i = 0; i < *max_size; i++) {
        Node* current = lists[i];
        while (current) {
            Node* temp = current;
            current = current->next;

            int new_index = hash_function(temp->data.size, new);

            temp->next = newLists[new_index];
            newLists[new_index] = temp;
        }
    }

    free(lists); 
    *max_size = new;
    return newLists;
}



void print_lists(Node** lists, int current_size, int num_of_items) {
    if(num_of_items == current_size) {
        printf("No duplicates found.\n");
        return;
    }

    for (int i = 0; i < current_size; i++) {
        Node* current = lists[i];
        while (current != NULL) {
            printf("Path: %s\n", current->data.path);
            printf("Size: %d\n", current->data.size);
            printf("Paired: %d\n", current->data.paired);
            current = current->next;
        }
    }
}


//this is what google recommends for a hash function, it is prime based hashing
int hash_function(off_t size, int max_size) {
    return abs(size * 2654435761) % max_size; // Prime-based hashing
}







