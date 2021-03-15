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
#include "memorymanager.h"

int running = 1;

struct PCB *head = NULL, *tail= NULL;


struct PCB* myinit(FILE *file, int nbPages, char* bs_filename) {
    struct PCB* pcb = makePCB(file, nbPages, bs_filename);
    addToReady(pcb);
    return pcb; 
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
            cpuSetIP(cur->counter, cur->PC_offset);

            int process_complete = run(cpu->quanta, cur);

            if(process_complete==2){
                cur->PC_page++;
                cur->PC_offset=0;
                if(cur->PC_page > cur->pages_max){ process_complete = 1;} 
                else{
                    int frameExists = cur->pageTable[cur->PC_page];
                    if( frameExists != -1){
                    	cur->counter= frameExists*4;
                    }
                    else{
                        int frameNb = findFrame();
                        int victimFrame = -1;
                        if(frameNb == -1){ victimFrame = findVictim(cur);}
                        if(frameNb != -1){ //hole
                            loadPage(cur->PC_page,cur->PC,frameNb);
                            cur->counter = frameNb*4;
                        }
                        else if(victimFrame != -1){ 
                            loadPage(cur->PC_page,cur->PC,victimFrame);
                            cur->counter = victimFrame*4;
                        }
                        updatePageTable(cur, cur->PC_page, frameNb, victimFrame);
                    }
                }
            }
            
            //modify
            //cur->PC = cpu->IP; 
           // cur->PC = *ram[frame];

            head = cur->next ? cur->next : cur;
            if(process_complete == 1) {
                free(cur);
                if(cur == head) head = NULL;
                 remove(cur->filename);
                cur = NULL;
            }
            else {
                addToReady(cur);
            }
            cpuSetIP(0,0);
       }
       
    }

    int r =0;
    while(ram[r] != NULL) {
        ram[r] = NULL;
        r++;
    }  
}

void boot() {
    system("rm -rf BackingStore");
    system("mkdir BackingStore");
    for(int i = 0; i < 40; i++) {
        ram[i] = NULL;
    }
    
}

int kernel(int argc, char* argv[]) {
    initCPU();

    printf("Kernel 1.0 loaded!\n");
    printf("Welcome to the Rebecca shell!\n"
           "Shell Version 2.0 Updated March 2020\n");

 
    int err = shellUI(argc, argv);


    return err;
}

 