#ifndef PCB_H_INCLUDE
#define PCB_H_INCLUDE

#include <stdio.h>

struct PCB* makePCB(FILE *file, int nbPages, char* name);
struct PCB {
    FILE* PC;
    struct PCB* next;
    int pageTable[10];
    int PC_page;
    int PC_offset;
    int pages_max;
    char* filename;
    int counter;
};

#endif