#include <stdio.h>
#include "kernel.h"


int main(int argc, char* argv[]) {
    int err=0;
    boot();
    err = kernel(argc, argv);
    
    return err;

 }  