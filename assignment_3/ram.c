#include <stdio.h>
#include<string.h>

#include "ram.h"

char *ram[40];

void addToRAM(FILE* page,int frameNb) {
	//frameNb btw 0 and 9
	int indexInRam = frameNb*4;
	int i=0;
    char line[100];
    while(i<4){  	
		fgets(line,99,page);
		if(feof(page) != 0|| page==NULL) break;
		//skip empty lines
		if( !(strcmp(line,"\n"  ) != 0 &&
		 	strcmp(line,"\r\n") != 0 &&
		  	strcmp(line,"\0"  ) != 0 &&1)){
		  	 continue;}
		ram[indexInRam]= strdup(line);
		indexInRam++;
		i++;
	}

}