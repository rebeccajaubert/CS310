#ifndef KERNEL_H_INCLUDE
#define KERNEL_H_INCLUDE

struct PCB;

extern int running;
extern struct PCB *head;
extern struct PCB *tail;
void myinit(FILE *filename);
void addToReady(struct PCB* pcb);
void scheduler();

#endif