#define  _POSIX_C_SOURCE 200809L

#include "merge.h"

mainArray_t *createMainArray(int size) {
    mainArray_t *mainArray = (mainArray_t*)calloc(1, sizeof(mainArray_t));
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
    int readOne;
    int readTwo;

    if(fileOne && fileTwo && output){
        int flag = 1;
        while(flag){
            readOne = getline(&lineOne, &lineOneSize, fileOne);
            readTwo = getline(&lineTwo, &lineTwoSize, fileTwo);
            if(readOne != -1){
                fwrite(lineOne, sizeof(*lineOne), readOne, output);
            }
            if(readTwo != -1){
                fwrite(lineTwo, sizeof(*lineTwo), readTwo, output);
            }
            if(readOne == -1 && readTwo == -1){
                flag = 0;
            }
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

rowsBlock_t *createRowsBlock(FILE *mergedFile){
    char *line = NULL;
    size_t lineSize = 0;
    int read;

    rowsBlock_t *rowsBlock = (rowsBlock_t*)calloc(1, sizeof(rowsBlock_t));

    if(mergedFile){
        rowsBlock->size = 0;
        while((read = getline(&line, &lineSize, mergedFile)) != -1){
            rowsBlock->size = rowsBlock->size + 1;
        }
        rewind(mergedFile);
        rowsBlock->rows = (char**)calloc(rowsBlock->size, sizeof(char*));

        free(line);
        line = NULL;
        lineSize = 0;     

        for(int i = 0; i < rowsBlock->size; i++){
            read = getline(&line, &lineSize, mergedFile);
            rowsBlock->rows[i] = line;
            line = NULL;
            lineSize = 0;     
        }
    }
    else{
        free(rowsBlock);
        free(line);
        fclose(mergedFile);
        printf("Error with mergedFile!\n");
        return NULL;
    }

    free(line);
    fclose(mergedFile);

    return rowsBlock;
}

int numberOfRows(mainArray_t* mainArray, int blockIndex){
    if(blockIndex < mainArray->size){
        rowsBlock_t *block = mainArray->rowsBlocks[blockIndex];

        if(block){
            return block->size;
        }
        else{
            printf("Block is empty!\n");
            return -1;
        }
    }
    else{
        printf("Block index out of range!\n");
        return -2;
    }
}

void removeRow(mainArray_t* mainArray, int blockIndex, int row){

    if(blockIndex < mainArray->size){
        rowsBlock_t *block = mainArray->rowsBlocks[blockIndex];

        if(block){
            if(row < block->size){
                free(block->rows[row]);
                while(row < block->size - 1){
                    block->rows[row] = block->rows[row + 1];
                    row = row + 1;
                }
                block->size = block->size - 1;
                block->rows[block->size] = NULL;
                char **toDelete = block->rows;
                block->rows = (char**)realloc(toDelete, block->size * sizeof(char*));
                if(toDelete != block->rows){
                    free(toDelete);
                }
            }
            else{
                printf("Block index out of range!\n");
            }
        }
        else{
            printf("Block is empty!\n");
        }

    }
    else{
        printf("Block index out of range!\n");
    }
}

void removeBlock(mainArray_t* mainArray, int blockIndex){
    if(blockIndex < mainArray->size){
        rowsBlock_t *block = mainArray->rowsBlocks[blockIndex];

        if(block){
            for(int i = 0; i < block->size; i++){
                free(block->rows[i]);
            }
            free(block->rows);
            free(block);
            mainArray->rowsBlocks[blockIndex] = NULL;
            
        }
        else{
            printf("Block is already empty!\n");
        }
    }
    else{
        printf("Block index out of range!\n");
    }
}


void printMergedBlocks(mainArray_t* mainArray){
    for(int i = 0; i < mainArray->size; i++){
        printf("Block number %d\n", i);
        if(mainArray->rowsBlocks[i]){
            for(int j = 0; j < mainArray->rowsBlocks[i]->size; j++){
                if(mainArray->rowsBlocks[i]->rows[j]){
                    printf("%s", mainArray->rowsBlocks[i]->rows[j]);
                }
                else{
                    printf("Empty row!\n");
                }
            }
        }
        else{
            printf("Empty block!\n");
        }
    }


}