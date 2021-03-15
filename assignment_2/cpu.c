#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "interpreter.h"
#include "pcb.h"
#include "cpu.h"
#include "kernel.h" 
#include "ram.h"

struct CPU* cpu;

void initCPU() {
    cpu = malloc(sizeof(struct CPU));
    cpu->quanta = 2;
    cpu->IP= 0;
}

void deleteCPU() {
    free(cpu);
}

void cpuSetIP(int PC) {
    cpu->IP = PC;
}

int cpuAvailable() {
    return cpu->IP == 0;
}

int run(int quanta,struct PCB* cur) {
     while(quanta > 0) {

        if(cpu->IP == cur->end ) return 1;

        strcpy((cpu->IR),ram[cpu->IP]);
    
        char* parsed_input[200];
        int words_parsed;

        cpu->IR[strlen(cpu->IR)-1] = '\0'; // remove \n character
        parse(cpu->IR, parsed_input, &words_parsed);
       // printf("parsed : %s\n", *parsed_input);

        //do not exit if quit in prog : just terminate prog
        if(strcmp(*parsed_input,"quit") ==0){
            return 1;
        }

        interpreter(parsed_input, words_parsed);

        
        (cpu->IP)++;
        quanta--;
     }

    return 0;
}