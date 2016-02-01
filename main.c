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
    puts("insert");
    puts("erase");
    puts("find");
    puts("exit");
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
        insert();

    if(!strcmp(command, "erase"))
        erase();

    if(!strcmp(command, "find"))
        find();

    if(!strcmp(command, "v"))
        viewAll();

    return 1;
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

    word->id = count;


}

void output(Word* word)
{
    printf("%d)%s -%s\n",word->id, word->keyword, word->mean);
}

void find(void)
{
    int i;

    puts("what you need find?");
    char s[100];
    gets(s);

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
//    char s[100];
//    gets(s);
    int id;
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(dictionary[i].id == id)
        {
            for(j = i; j < count; j++)
            {
                dictionary[j] = dictionary[j + 1];
            }

            dictionary = (Word*) realloc(dictionary, sizeof(Word) * (count - 1));
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
    if((fp = fopen("//home//danek//save.txt", "w")) == NULL)
        puts("could not open or creat this file");

    int i;

    for(i = 0; i < count; i++)
    {
        fprintf(fp, "#%s\n", dictionary[i].keyword);
        fprintf(fp, "%s\n", dictionary[i].mean);
    }

    fclose(fp);
}


void openFile(char* path)
{
    FILE* fp;

    if((fp = fopen(path, "r")) == NULL)
    {
        puts("could not open or creat this file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    unsigned int file_size = ftell(fp);

    char* file_array = (char*) malloc(file_size);

    if(file_array == 0) puts("fatal error");

    fseek( fp , 0 , SEEK_SET );

    int res = fread(file_array, 1, file_size, fp);
    if(res != file_size) printf("2 fatal %d", res);

    int i;
    unsigned int word_count;

    for(i = 0; i < file_size; i++)
    {
        if(file_array[i] == '#')
            word_count++;
    }

    dictionary = (Word*) realloc(dictionary, sizeof(Word) * (count + word_count));


    char s[1048576];
    int j = 0;
    byte_t flag;

    for(i = 0; i < file_size; i++)
    {
        if(file_array[i] == '\n')
            continue;

        if(file_array[i] == '#')
        {
            count++;
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
            dictionary[count - 1].keyword[j++] = file_array[i];
        }

        if(flag == 0)
        {
            dictionary[count - 1].mean = (char*) realloc(dictionary[count - 1].mean, j);
            dictionary[count - 1].mean[j++] = file_array[i];
        }



    }

}


int main(int argc, char *argv[])
{
    int i;

    if(argc != 1)
    for(i = 1; i < argc; i++)
    {
        openFile(argv[i]);
        printf("%s\n", argv[i]);
    }

    dictionary = (Word*) realloc(dictionary, sizeof(Word));
 
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
