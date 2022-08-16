#include <stdio.h>

#define NEW_MATRIX(rows, cols, type, name) {\
            name = (type**)(malloc(sizeof(type*) * rows));\
            for(int i = 0; i < (sizeof(name) / sizeof(type)); i++)\
                name[i] = (type*)(malloc(sizeof(type) * cols));\
        }

#define FREE_MATRIX(name, type) {\
            for(int i = 0; i < (sizeof(name) / sizeof(type)); i++)\
                free(name[i]);\
            free(name) ;\
        }
