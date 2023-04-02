#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main (int argc, char *argv[]){
    int pid1,pid2, len, i;
    char name[255]={"\0"}, Error[255]={'\0'};


    if (argc != 5)
    {// ean den exei ta kataleila orismata
        printf("./project4 <progname>.c <progname>.args <progname>.in <progname>.out");
        return 0;
    }

    
    len = strlen(argv[1]);
    for ( i = 0; i < len - 2; i++)
    {
        name[i] = argv[1][i];
    }
    
    strcat(Error, "2>");
    strcat(Error, name);
    strcat(Error, ".err");

    if( !(pid1 = fork() )){
        
        execl("/usr/bin/gcc", "-Wall", argv[1], "-o", name, Error, NULL);

    }

    return 0;
}