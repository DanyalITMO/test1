#ifndef DATA_H
#define DATA_H

#define MAX_LENGHT_WORD 128

typedef unsigned char  byte_t;

typedef struct
{
    char keyword[MAX_LENGHT_WORD];
    char* mean;
    unsigned int id;
}Word;


Word*  dictionary;
int count;


#endif
