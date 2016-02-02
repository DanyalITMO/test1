#ifndef COMMAND_LINE
#define COMMAND_LINE

#include "data.h"

void help(void);
byte_t control(char*);
char* myGetline(char* ,unsigned int);
void input(Word*);
void output(Word*);
void find(void);
void erase(void);
void insert(void);
void viewAll(void);

#endif
