#include <stdio.h>
#include <string.h>

#include "file_operation.h"
#include "data.h"

void saveFile(void)
{
    FILE* fp;

    //if((fp = fopen("//home//danek//save.txt", "w")) == NULL)

    if((fp = fopen("save.txt", "w")) == NULL)
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

    free(file_array);
    fclose(fp);
}
