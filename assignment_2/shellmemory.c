#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct MEM{
    char* var;
    char* value;
};

struct MEM shellMem[1000];


void shell_set(char* var, char* val) {

 	struct MEM* pp2 = &shellMem[0];

     while(pp2->var) { 
        if(strcmp(pp2->var, var) == 0) {
            pp2->value = strdup(val);
            break;
        }
        pp2 = pp2+1;    
    }
    
    if(!(pp2->var)){ 
    	pp2->var = strdup(var);
    	pp2->value =strdup(val);
    	pp2 = pp2+1;

    }
  
}

int shell_get(char* var) {

    struct MEM* pp2 = &shellMem[0];

    while(pp2->var) { 
        

        if(strcmp(pp2->var, var) == 0) {
        	printf("%s\n", pp2->value);
            return 0;
        }
        pp2 = pp2+1;    
    }

    printf("Variable does not exist\n");
    return 1;
}
