#include <stdio.h>

#include "file_operation.h"
#include "command_line.h"
#include "data.h"


int main(int argc, char *argv[])
{
    dictionary = (Word*) realloc(dictionary, sizeof(Word));

    int i;

    if(argc != 1)
    for(i = 1; i < argc; i++)
    {
        openFile(argv[i]);
    }

 
    byte_t flag = 1;
   
    char* command;
    while(flag)
     {
         help();

         command = myGetline(command, 0);
         flag = control(command);
     }
    return 0;
}
