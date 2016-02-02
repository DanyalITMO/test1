#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

void saveFile(void);//save dictionary

unsigned int fileSize(FILE* fp);

char* writeFileInBuffer(FILE *fp, char* file_array); //read file in file_array(heap)

unsigned int wordCounter(char* file_array, unsigned int file_size);//number of words in file_arrat

void openFile(char* path);//open dictionary file


#endif
