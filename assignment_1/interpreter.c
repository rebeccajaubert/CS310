#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "shellmemory.h"

int help();
int quit();
int set(char*, char*);
int get(char*);
int script(char* words[]);

int interpreter(char* words[]) {
    if(words == NULL) return -1;
    else if(!words[0] || strlen(words[0]) == 0) return 0; // if no input given we skip

    int errCode = 0;


    if(strcmp(words[0], "help") == 0) errCode = help();
    else if(strcmp(words[0], "quit") == 0) errCode = quit();
    else if(strcmp(words[0], "set") == 0) errCode = set(words[1], words[2]);
    else if(strcmp(words[0], "print") == 0) errCode = get(words[1]);
    else if(strcmp(words[0], "run") == 0) errCode = script(words);
    else {
        printf("%s: unknown command\n", words[0]);
        errCode = -1;
    } 
    return errCode;
}

int help() {
    printf("help\t-\tDisplays all the commands\n"
        "quit\t-\tExits/Terminates the shell with \"Bye\"\n"
        "set VAR STRING\t-\tAssigns a value to shell memory\n"
        "print VAR\t-\tPrints the STRING assigned to VAR\n"
        "run SCRIPT.TXT\t-\tExecutes the file SCRIPT.TXT\n");

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
        interpreter(parsed_line);

        if(running == 0) break;
       
        // clear parsed lines 
        for(int i = 0; i < word_count; i++) *parsed_line[i] = '\0';

        fgets(line, 999, file);
    }

    fclose(file);
    return 0;
}
