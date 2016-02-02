#include <stdio.h>
#include <string.h>

typedef unsigned char  byte_t;

typedef struct
{
    char keyword[128];
    char* mean;
    unsigned int id;
}Word;


Word*  dictionary;
int count;


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

void saveFile()
{
    FILE* fp;
    if((fp = fopen("~//save.txt", "w")) == NULL)
        puts("could not open or creat this file");

    int i;

    for(i = 0; i < count; i++)
    {
        fprintf(fp, "#%s\n", dictionary[i].keyword);
        fprintf(fp, "%s\n", dictionary[i].mean);
    }

    fclose(fp);
}

unsigned int fileSize(FILE* fp)
{
    fseek(fp, 0, SEEK_END);
    unsigned int file_size = ftell(fp);
    fseek( fp , 0 , SEEK_SET );

    return file_size;
}

char* writeFileInBuffer(FILE *fp, char* file_array) //read file in file_array(heap)
{
    unsigned int file_size = fileSize(fp);

    file_array = (char*) malloc(file_size);

    if(file_array == 0)
    {
        puts("bad allocate. Dictionary can not be connected");
    }

    int res = fread(file_array, 1, file_size, fp);

    if(res != file_size)
    {
        puts("Dictionary can not be read");
        return;
    }

    return file_array;
}

unsigned int wordCounter(char* file_array, unsigned int file_size)
{
    int i;
    unsigned int word_count = 0;

    for(i = 0; i < file_size; i++)
    {
        if(file_array[i] == '#')
            word_count++;
    }

    return word_count;

}


void openFile(char* path)
{
    FILE* fp;

    if((fp = fopen(path, "r")) == NULL)
    {
        puts("could not open or creat this file");
        return;
    }

    unsigned int file_size = fileSize(fp);
    char*  file_array = writeFileInBuffer(fp, file_array);

    if(file_array == NULL)
        return;

    unsigned int word_count = wordCounter(file_array, file_size);


    dictionary = (Word*) realloc(dictionary, sizeof(Word) * (count + word_count));

    if(dictionary == NULL)
    {
        puts("bad allocate");
        return;
    }


    int i, j = 0;
    byte_t flag;

    for(i = 0; i < file_size; i++)
    {
        if(file_array[i] == '\n')
            continue;

        if(file_array[i] == '#')
        {
            count++;
            dictionary[count -1].id = count -1;

            flag = 1;
            j = 0;
            continue;
        }

        if(file_array[i - 1] == '\n' && file_array[i] != '#')
        {

            flag = 0;
            j = 0;
        }

        if(flag == 1)
        {
            dictionary[count - 1].keyword[j + 1] = '\0'; //end of the line is always ahead of the last symbol
            dictionary[count - 1].keyword[j++] = file_array[i];
        }

        if(flag == 0)
        {
            dictionary[count - 1].mean = (char*) realloc(dictionary[count - 1].mean, j + 2);

            if(dictionary == NULL)
            {
                puts("bad allocate");
                return;
            }

            dictionary[count - 1].mean[j + 1] = '\0';//end of the line is always ahead of the last symbol
            dictionary[count - 1].mean[j++] = file_array[i];
        }



    }

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
