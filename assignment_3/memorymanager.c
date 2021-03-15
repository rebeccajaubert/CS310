#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "pcb.h"
#include "ram.h"
#include "kernel.h"
#include "memorymanager.h"

int backstore_count = 0;

void loadPage(int pageNumber, FILE *PC, int frameNumber){
    addToRAM(PC, frameNumber);
}



int launcher(FILE* p) {
    //copy
    char bs_filename[200];
    sprintf(bs_filename, "BackingStore/prog%d.txt", backstore_count++);
    //open in BS
    FILE* bs_file = fopen(bs_filename, "w+");

    char c;
    while((c = fgetc(p)) != EOF) fputc(c, bs_file);
    //close original pointer
    fclose(p);

    int nbPages = countTotalPages(bs_file);
  
   struct PCB* pcb = myinit(bs_file, nbPages, bs_filename);  //create pcb, add to ready queue
    
    // load in max 2 pages from backstore into RAM
    int pagesToLoad = nbPages > 1 ? 2 : nbPages;
    for(int i = 0; i < pagesToLoad; i++){
		int frameNb = findFrame();
   		int victimFrame = -1;
   		if(frameNb == -1){ victimFrame = findVictim(pcb);}
        if(frameNb != -1){loadPage(i, pcb->PC, frameNb); 
        if(i==0)pcb->counter = frameNb*4; //issue?
        }
        else if(victimFrame != -1){
         loadPage(i, pcb->PC, victimFrame);
         if(i==0)pcb->counter= victimFrame*4; //issue?
        }
        updatePageTable(pcb, i, frameNb, victimFrame);
    }
    return 0;
}

int countTotalPages(FILE* f) {
    int pos = ftell(f);                     
    fseek(f, 0, SEEK_SET);
    char buffer[1000];
    int count = 0;
    if(f == NULL) {
      perror("Error opening file");
      return(-1);
   }
    while( fgets(buffer,1000,f)!=NULL ){count++;}
    fseek(f, 0, SEEK_SET);
    return ceil(count / 4.0);
}


int findFrame() {
    for(int i = 0; i < 10; i++) {
        if(ram[i*4] == NULL) {
            return i;
        }
    }

    return -1;
}

int findVictim(struct PCB* pcb) {
    srand(0);
    int victim = rand() % 10;
    //is it same pcb ?
    if(pcb->pageTable[victim] == -1) return victim;

    else{
        for(int i = 0; i < 10; i++) {
            if(pcb->pageTable[++victim %10] == -1) return victim;
        }

        fprintf(stderr, "Unable to find page victim which does not belong to PCB\n");
        exit(-1);
    }

    return -1;
}



int updatePageTable(struct PCB* p, int pageNumber, int frameNumber, int victimFrame) {
    
    if(frameNumber == -1){ 
        p->pageTable[pageNumber] = victimFrame;
        //update victim page table
        struct PCB* pcbVictim = head;
        while(pcbVictim){
            if(pcbVictim->pageTable[victimFrame] != -1){
                pcbVictim->pageTable[victimFrame] = -1;
            }
            pcbVictim = pcbVictim->next;
        }
    }
    else { p->pageTable[pageNumber] = frameNumber; }

    return 1;
}


