#include <stdio.h>
#include <windows.h>
#include "config.h"

void writeToFile(WCHAR ch){
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL){
        printf("Error opening file\n");
        return;
    }
    if (fputc(ch, file) == EOF){
        printf("Error writing to file\n");
    }
    fclose(file);
}