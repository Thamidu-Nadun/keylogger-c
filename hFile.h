#include "common.h"
#include "config.h"

#define FULL_FILE_PATH FILE_PATH "\\" FILE_NAME

void ensureFileExists(){
    CreateDirectory(FILE_PATH, NULL);
}
void writeToFile(WCHAR ch){
    ensureFileExists();
    FILE *file = fopen(FULL_FILE_PATH, "a");
    if (file == NULL){
        printf("Error opening file\n");
        return;
    }
    if (fputc(ch, file) == EOF){
        printf("Error writing to file\n");
    }
    fclose(file);
}