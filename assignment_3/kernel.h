#ifndef KERNEL_H_INCLUDE
#define KERNEL_H_INCLUDE

struct PCB;

extern int running;
extern struct PCB *head;
extern struct PCB *tail;
struct PCB* myinit(FILE *filename, int nbPages, char* name);
void addToReady(struct PCB* pcb);
void scheduler();
void boot();
int kernel(int argc, char* argv[]);

#endif