#include <stdlib.h>

#include "pcb.h"

struct PCB* makePCB(int startInst, int endInst) {
    struct PCB* pcb = malloc(sizeof(struct PCB));
    pcb->PC = startInst;
    pcb->start = startInst;
    pcb->end = endInst;
    pcb->next = NULL;

    return pcb;
}

