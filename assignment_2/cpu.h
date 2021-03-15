#ifndef CPU_H_INCLUDE
#define CPU_H_INCLUDE

#include <stdio.h>

void initCPU();
void deleteCPU();
int run(int quanta,struct PCB* cur);
int cpuAvailable();
void cpuSetIP(int PC);

struct CPU {
    int IP;
    char IR[1000];
    int quanta;
};
extern struct CPU *cpu; 
#endif