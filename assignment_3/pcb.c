#include <stdlib.h>
#include <string.h>

#include "pcb.h"

struct PCB* makePCB(FILE *file, int nbPages, char* name) {
    struct PCB* pcb = malloc(sizeof(struct PCB));
    pcb->filename = strdup(name);
    pcb->PC= file;
    pcb->next = NULL;
    pcb->PC_page = 0;
    pcb->PC_offset = 0;
    pcb->pages_max = nbPages;
    for(int i = 0; i < 10; i++) pcb->pageTable[i] = -1;
    pcb->counter=0;
    return pcb;
}
