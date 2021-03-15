#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "interpreter.h"

int shellUI(int argc, char* argv[]) {

    char prompt[100] = {'$','\0'};
    char command[1000];
    char* parsed_command[300];
    int errorCode =0;

    while(running) {
        printf("%s ",prompt);
         
        fgets(command, 999, stdin);

        int size = strlen(command);
        if(size == 0) break;
        else command[size-1] = '\0'; // remove the \n appended
        
        int words_parsed = 0;

        errorCode = parse(command, parsed_command, &words_parsed);
        if(errorCode!=0) return 99;     
        interpreter(parsed_command, words_parsed);
        
        // clear strings in parsed_input
        for(int i = 0; i < words_parsed; i++) *parsed_command[i] = '\0';
    }

    return 0;
}

int parse(char* ui, char* output[], int* words_parsed) {
    char tmp[300];

    int ptr = 0;
    while(ptr < 1000 && ui[ptr] == ' ') ptr++;

    int sp = 0;
    while(ptr < 1000 && ui[ptr] != '\0') {
        int wp = 0;

        while(ptr < 1000 && wp < 300 && ui[ptr] != '\0' && 
              (ui[ptr] != ' ' ||sp>=3) ){
               //I needed to add this line to get rid of carriage return when getting commands from a file
                if(ui[ptr] == 13) {ptr++; continue;}
               tmp[wp++] = ui[ptr++];
        }

    

        if(wp == 300) {
            printf("word in command given exceeds max char count (300)\n");
            return -1;
        }

        tmp[wp] = '\0';

        output[sp++] = strdup(tmp);

        if(ptr < 1000 && ui[ptr] == ' ') ptr++;
    }

    *words_parsed = sp;
    return 0;
}
