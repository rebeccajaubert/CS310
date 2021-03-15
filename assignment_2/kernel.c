#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include "shell.h"
#include "kernel.h"
#include "interpreter.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"

int running = 1;

struct PCB *head = NULL, *tail= NULL;


void myinit(FILE *filename) {
    int start=0;
    int end =0;
    addToRAM(filename, &start,&end);

    struct PCB* pcb = makePCB(start, end);
    addToReady(pcb);
      
}

void addToReady(struct PCB* pcb) {
    if(head == NULL){
        head = pcb;
        tail=pcb;
    }
    else {
        tail->next = pcb;
        tail = pcb;
        tail->next = NULL;
    }
}

void scheduler() {
    while(head) {
        if(cpuAvailable()) {        
            struct PCB* cur = head;

            cpuSetIP(cur->PC);

          //  printf("start PCB: %d,end PCB: %d, cur PC: %d\n", cur->start,cur->end, cur->PC);

            int process_complete = run(cpu->quanta, cur);

            cur->PC = cpu->IP; 

            head = cur->next ? cur->next : cur;
            if(process_complete) {
                free(cur);
                if(cur == head) head = NULL;
                cur = NULL;
            }
            else {
                addToReady(cur);
            }
          //  printf("cpu IP %d\n", cpu->IP);
            cpuSetIP(0);
       }
    }
    int r =0;
    while(ram[r] != NULL) {
        ram[r] = NULL;
        r++;
    }
    
}

int main(int argc, char* argv[]) {
    initCPU();

    printf("Kernel 1.0 loaded!\n");
    printf("Welcome to the Rebecca shell!\n"
           "Shell Version 2.0 Updated February 2020\n");

 
    shellUI(argc, argv);


    return 0;
}