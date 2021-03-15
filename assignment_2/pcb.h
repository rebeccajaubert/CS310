#ifndef PCB_H_INCLUDE
#define PCB_H_INCLUDE

#include <stdio.h>

struct PCB* makePCB(int start, int end);
struct PCB {
    int PC;
    int start;
    int end;
    struct PCB* next;
};

#endif