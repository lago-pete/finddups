#include "finddups.h"






int main(int argc, char *argv[]) {
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

