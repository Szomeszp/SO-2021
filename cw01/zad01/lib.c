#include "lib.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <stddef.h>

mainArray_t *createMainTable(size_t size) {
    mainArray_t *mainArray = calloc(1, sizeof(mainArray_t));
    mainArray->size = size;
    mainArray->rowsBlocks = (rowsBlock_t**)calloc(mainArray->size , sizeof(rowsBlock_t*));
    return mainArray;
}

FILE *mergeFiles(char *firstFile, char *secondFile){
    FILE *fileOne = fopen(firstFile, "r");
    FILE *fileTwo = fopen(secondFile, "r");
    FILE *output = tmpfile();

    char *lineOne = NULL;
    char *lineTwo = NULL;
    size_t lineOneSize = 0;
    size_t lineTwoSize = 0;
    ssize_t readOne;
    ssize_t readTwo;

    if(fileOne && fileTwo && output){
        while((readOne = getline(&lineOne, &lineOneSize, fileOne)) != -1 && (readTwo = getline(&lineTwo, &lineTwoSize, fileTwo) != -1)){
            fwrite(lineOne, sizeof(lineOne), readOne, output);
            fwrite(lineTwo, sizeof(lineTwo), readTwo, output);
        }
        while((readOne = getline(&lineOne, &lineOneSize, fileOne)) != -1){
            fwrite(lineOne, sizeof(lineOne), readOne, output);
        }
        while((readTwo = getline(&lineTwo, &lineTwoSize, fileTwo) != -1)){
            fwrite(lineTwo, sizeof(lineTwo), readTwo, output);
        }        
    }
    else{
        if(output){
            fclose(output);
            output = NULL;
        }
    }
    if(fileOne){
        fclose(fileOne);
    }
    if(fileTwo){
        fclose(fileTwo);
    }

    free(lineOne);
    free(lineTwo);

    rewind(output);

    return output;
}

void createRowsBlock(mainArray_t *mainArray, FILE *mergedFile){
    char *line = NULL;
    size_t lineSize = 0;
    ssize_t read;

    if(mergedFile){
        rowsBlock_t *rowsBlock = calloc(1, sizeof(rowsBlock_t));
        rowsBlock->size = 0;
        while((read = getline(&line, &lineSize, mergedFile)) != -1){
            rowsBlock->size = rowsBlock->size + 1;
        }
        rewind(mergedFile);
        rowsBlock->rows = calloc(rowsBlock->size, sizeof(char*)); //sprawdzić czy trzeba rzutować na char**

        line = NULL;
        lineSize = 0;     

        for(int i = 0; i < rowsBlock->size; i++){
            read = getline(&line, &lineSize, mergedFile);
            rowsBlock->rows[i] = strdup(line);
        }
    }
    else{
        printf("No such file.");
    }

    free(line);

}


int main() {
    mainArray_t* m = createMainTable(2);
    return EXIT_SUCCESS;
}
