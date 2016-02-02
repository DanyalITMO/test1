#include <stdio.h>
#include <string.h>

#include "file_operation.h"
#include "data.h"


void help(void)
{
    puts("\n\n-----------");
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
        free(dictionary);
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



char* myGetline(char* string,unsigned int max_lenght)
{
    char c;
    string = (char*) malloc(1);
    long long i;

    while(1)
    {
        for(i = 1; (c = getchar()) != '\n'; i++)//input string
        {
            string = (char*) realloc(string, i);
            string[i-1] = c;
        }

        if(max_lenght > 0 && strlen(string) > max_lenght)
            puts("error. lenght > max\n. Try again");
        else
            break;
    }

    string = (char*) realloc(string, i); // input \0
    string[i - 1] = '\0';

    return string;

}

void input(Word* word)
{
    puts("\nenter word. Max 128 character:");
    char* buf = myGetline(buf, MAX_LENGHT_WORD);
    strcpy(word->keyword, buf);

    puts("enter mean:");
    word->mean = myGetline(word->mean, 0);

    word->id = count - 1; // input id

}


void output(Word* word) // print one ellement
{
    printf("%d)%s -%s\n",word->id, word->keyword, word->mean);
}

void find(void) //Search for a word in the dictionary
{
    int i;

    puts("what you need find? Max 128 character: ");
    char *s = myGetline(s, MAX_LENGHT_WORD);//1 mb

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
   
    char* command;
    while(flag)
     {
         help();

         command = myGetline(command, 0);
         flag = control(command);
     }
    return 0;
}
