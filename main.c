#include <stdio.h>
#include <string.h>

#include "file_operation.h"
#include "data.h"


void help(void)
{
    puts("-----------");
    puts("view - watch all words");
    puts("insert - insert the words at the end of the dictionary");
    puts("erase - Remove words by its number");
    puts("find - search interpretations");
    puts("exit - exit and save the file");
    puts("-----------");
    puts("\n");
}

byte_t control(char* command)
{

    if(!strcmp(command, "exit"))
    {
        saveFile();
        return 0;
    }

    if(!strcmp(command, "insert"))    
    {
        insert();
        return 1;
    }

    if(!strcmp(command, "erase"))
    {
        erase();
        return 1;
    }

    if(!strcmp(command, "find"))
    {
        find();
        return 1;
    }

    if(!strcmp(command, "view"))
    {
        viewAll();
        return 1;
    }

}

void input(Word* word)
{
    char s[1048576];//1 mb

    while(1) //input keyword
    {
        puts("enter word. Max 128 symbols");
        gets(s);

        if(strlen(s) > 128)
            puts("Error. line size > 128, try again\n");
        else
        {
            strcpy(word->keyword, s);
            break;
        }

    }

    while(1) //input mean
    {
        puts("\n enter mean");
        gets(s);
        word->mean = (char*) realloc(word->mean, sizeof(s));

        if(word->mean == NULL)
        {
           puts("allocate error. Try again");
           return 1;
        }
        else
        {
            strcpy(word->mean, s);
            break;
        }
    }

    word->id = count; // input id

}


void output(Word* word) // view one ellement
{
    printf("%d)%s -%s\n",word->id, word->keyword, word->mean);
}

void find(void) //Search for a word in the dictionary
{
    int i;

    puts("what you need find?");
    char s[1048576];//1 mb

    while(1) //input keyword
    {
        puts("enter word. Max 128 symbols");
        gets(s);

        if(strlen(s) > 128)
            puts("Error. line size > 128, try again\n");
        else
        {
            break;
        }

    }


    for(i = 0; i < count; i++)
    {
        if(!strcmp(dictionary[i].keyword, s))
            output(&dictionary[i]);
    }

}

void erase(void)
{
    int i, j;

    puts("what you need delete?. Enter id");
    int id;
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(dictionary[i].id == id)// if id coincided
        {
            for(j = i; j < count; j++)
            {
                dictionary[j] = dictionary[j + 1]; // lowe id all the following words on one

            }

            dictionary = (Word*) realloc(dictionary, sizeof(Word) * (count - 1)); // and realloc dictionary
            count--;
        }
    }
}


void insert(void)
{
    count++;
    dictionary = (Word*) realloc(dictionary, sizeof(Word) * (count));
    input(&dictionary[count - 1]);

}

void viewAll(void)
{
    int i;
    for( i = 0; i < count; i++)
        output(&dictionary[i]);
}



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
   
    char command[100];
    while(flag)
     {
         help();
         gets(command);
         flag = control(command);
     }
    return 0;
}
