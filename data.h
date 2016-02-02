#ifndef DATA_H
#define DATA_H

typedef unsigned char  byte_t;

typedef struct
{
    char keyword[128];
    char* mean;
    unsigned int id;
}Word;


Word*  dictionary;
int count;


#endif
