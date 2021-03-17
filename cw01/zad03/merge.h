#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct rowsBlock {
    char **rows;
    int size;
} rowsBlock_t;

typedef struct mainArray {
    rowsBlock_t **rowsBlocks;
    int size;
} mainArray_t;


mainArray_t *createMainArray(int size);

rowsBlock_t *createRowsBlock(FILE *mergedFile);
FILE *mergeFiles(char *firstFile, char *secondFile);

int numberOfRows(mainArray_t* mainArray, int blockIndex);

void removeBlock(mainArray_t* mainArray, int blockindex);
void removeRow(mainArray_t* mainArray, int blockIndex, int row);

void printMergedBlocks(mainArray_t* mainArray);