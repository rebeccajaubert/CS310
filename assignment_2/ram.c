#include <stdio.h>
#include<string.h>

#include "ram.h"

char *ram[1000];

void addToRAM(FILE* p, int *start, int *end) {
	int i=0;
    for( i = 0; i < 1000; i++) {
        if(ram[i] == NULL) {
            *start = i;
            break;
        }
    }

    char line[1000];
	while(!feof(p)){
		if(i==999){printf("Ram capacity exceeded, PCB will not be created\n"); break;}
		fgets(line,999,p);
		//skip empty lines
		if( !(strcmp(line,"\n"  ) != 0 && strcmp(line,"\r\n") != 0 && strcmp(line,"\0"  ) != 0 &&1)){ continue;}
		ram[i]= strdup(line);
		i++;
	}
	*end =i-1;
}