#include "finddups.h"






int main(int argc, char *argv[]) {
    table hashed_table;
    hashed_table.size = 0;
    hashed_table.buckets = NULL;

    

    if (argc < 2) {
        path(".");
    } else {
        for (int i = 1; i < argc; i++) {
            path(argv[i]);
        }
    }

    // TODO: Call function to identify and print duplicate files

    return 0;
}

