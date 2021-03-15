#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "shell.h"
#include "shellmemory.h"
#include "kernel.h"
//#include "ram.h"
//#include "pcb.h"

int help();
int quit();
int set(char*, char*);
int get(char*);
int script(char* words[]);
int exec(char* words[], int nbProg);

int interpreter(char* words[], int nbArgs) {
    if(words == NULL) return -1;
    else if(!words[0] || strlen(words[0]) == 0) return 0; // if no input given we skip

    int errCode = 0;


    if(strcmp(words[0], "help") == 0) errCode = help();
    else if(strcmp(words[0], "quit") == 0) errCode = quit();
    else if(strcmp(words[0], "set") == 0){ errCode = set(words[1], words[2]);}
    else if(strcmp(words[0], "print") == 0) errCode = get(words[1]);
    else if(strcmp(words[0], "run") == 0) errCode = script(words);
    else if(strcmp(words[0], "exec") == 0) errCode = exec(words, nbArgs);
    else {
        printf("%s: unknown command\n", words[0]);
        errCode = -1;
    } 
    return errCode;
}

int exec(char* words[], int nbProg){
    if(nbProg > 4) {
        printf("enter 3 programs at max\n");
        return -1;
    }
    else if(nbProg == 1) {
        return 0;
    }

    char* files_opened[3] = {NULL, NULL, NULL};

    for(int i = 1; i < nbProg; i++) {
        int open = 1;
        for(int j = 0; j < 3; j++) {
            if(files_opened[j] == NULL) break;

            if(strcmp(words[i], files_opened[j]) == 0) {
                printf("Error: script %s already loaded\n", words[i]);
                open = 0;
                break;
            }
        }

        if(open) {
            files_opened[i-1] = words[i];
            FILE* cur = fopen(words[i], "r");
            if(!cur) {
                printf("Script %s not found\n", words[i]);
            }
            else{
                myinit(cur);
            } 
        }
    }

    scheduler();

    return 0;
}

int help() {
    printf("help\t-\tDisplays all the commands\n"
        "quit\t-\tExits/Terminates the shell with \"Bye\"\n"
        "set VAR STRING\t-\tAssigns a value to shell memory\n"
        "print VAR\t-\tPrints the STRING assigned to VAR\n"
        "run SCRIPT.TXT\t-\tExecutes the file SCRIPT.TXT\n"
        "exec prog1 prog2 prog3\t-\tExecutes concurrent programs\n");

    return 0;
}

int quit() {
    running = 0;
    printf("Bye!\n");
    return 0;
}

int set(char* var, char* value) {
    shell_set(var, value);
    return 0;
}

int get(char* var) {
    shell_get(var);
    return 0;
}

int script(char* words[]) {
    char line[1000];
    FILE* file = fopen(words[1], "rt");
    if(!file) {
        printf("Script not found\n");
        return -1;
    }

    char* parsed_line[300];
    int line_number = 1;
    fgets(line, 999, file);
    while(!feof(file)) {
        int word_count = 0;
       
        line[strlen(line)-1] = '\0'; // remove \n character
        parse(line, parsed_line, &word_count);
        interpreter(parsed_line, word_count);

        if(running == 0) break;
       
        // clear parsed lines 
        for(int i = 0; i < word_count; i++) *parsed_line[i] = '\0';

        fgets(line, 999, file);
    }

    fclose(file);
    return 0;
}
