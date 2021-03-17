#include "merge.h"
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>

char *generateRandomString(int length) {
  char *randomString = calloc(length + 1, sizeof(char));
  for (int i = 0; i < length - 1; i++) {
    randomString[i] = (char) 65 + (rand() % 26);
  }
  randomString[length - 1] = '\n';
  randomString[length] = '\0';
  return randomString;
}

void generateRandomFile(char *name, int rows){
    int randomLength;
    char *randomString;
    FILE *file = fopen(name, "w+");
    for(int i = 0; i < rows; i++){
        randomLength = rows / 2 + (rand() % rows / 2);
        randomString = generateRandomString(randomLength);
        fwrite(randomString, sizeof(char), randomLength, file);
        free(randomString);
        randomString = NULL;
    }
    fclose(file);
}

void runTest(){
    mainArray_t *mainArray = NULL;

    int size[3] = {16, 256, 1024};
    clock_t startReal;
    clock_t endReal;
    struct tms start;
    struct tms end;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            generateRandomFile("testFileA.txt", size[j]);
            generateRandomFile("testFileB.txt", size[j]);

            FILE **mergedFiles = (FILE**)calloc(size[i], sizeof(FILE*));

            mainArray = createMainArray(size[i]);

            printf("\n====================================\n");
            printf("Testing %d pairs of max length %d...\n", size[i], size[j]);
            printf("====================================\n");

            startReal = clock();
            times(&start);
            for(int k = 0; k < size[i]; k++){                
                mergedFiles[k] = mergeFiles("testFileA.txt", "testFileB.txt");
            }
            endReal = clock();
            times(&end);

            printf("\nMerging times:\n");
            printf("Real time: %f || User time: %f || System time: %f\n", (double)(endReal - startReal)/CLOCKS_PER_SEC, (double)(end.tms_utime - start.tms_utime)/sysconf(_SC_CLK_TCK), (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

            startReal = clock();
            times(&start);
            for(int k = 0; k < size[i]; k++){                
                mainArray->rowsBlocks[k] = createRowsBlock(mergedFiles[k]);
            }
            endReal = clock();
            times(&end);

            printf("\nBlock creating times:\n");
            printf("Real time: %f || User time: %f || System time: %f\n", (double)(endReal - startReal)/CLOCKS_PER_SEC, (double)(end.tms_utime - start.tms_utime)/sysconf(_SC_CLK_TCK), (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

            startReal = clock();
            times(&start);
            for(int k = 0; k < size[i]; k++){                
                removeBlock(mainArray, k);
            }
            free(mainArray);
            endReal = clock();
            times(&end);

            printf("\nBlock deleting times:\n");
            printf("Real time: %f || User time: %f || System time: %f\n", (double)(endReal - startReal)/CLOCKS_PER_SEC, (double)(end.tms_utime - start.tms_utime)/sysconf(_SC_CLK_TCK), (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));
        }
    }
}

int main(int argc, char **argv){
    mainArray_t *mainArray = NULL;
    srand(time(NULL));    

    if(argc > 2){
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "create_table") == 0){
                int size = atoi(argv[++i]);
                mainArray = createMainArray(size);
                mainArray->size = size;
                printf("Main array of size %d has been created!\n", size);
            }
            else if(strcmp(argv[i], "merge_files") == 0){
                if(mainArray){
                    int mergedFiles = 0;
                    while(mergedFiles < mainArray->size){
                        char *firstFile = strtok(argv[++i], ":");
                        char *secondFile = strtok(NULL, ":");

                        if(firstFile && secondFile){
                            FILE *merged = mergeFiles(firstFile, secondFile);
                            int ptr = 0;
                            while(mainArray->rowsBlocks[ptr] != NULL){
                                ptr = ptr + 1;
                            }
                            mainArray->rowsBlocks[ptr] = createRowsBlock(merged);
                            printf("File %s and file %s has been merged!\n", firstFile, secondFile);
                        }
                        else{
                            printf("Error while opening files!\n");
                            return -1;
                        }
                        mergedFiles = mergedFiles + 1;
                    }
                }
                else{
                    printf("Main array has not been created yet!\n");
                    return -1;
                }
            }
            else if(strcmp(argv[i], "remove_block") == 0){
                if(mainArray){
                    removeBlock(mainArray, atoi(argv[++i]));
                }
                else{
                    printf("Main array has not been created yet!\n");
                    return -1;
                }
            }
            else if(strcmp(argv[i], "remove_row") == 0){
                if(mainArray){
                    int blockIndex = atoi(argv[++i]);
                    int rowIndex = atoi(argv[++i]);
                    removeRow(mainArray, blockIndex, rowIndex);
                }
                else{
                    printf("Main array has not been created yet!\n");
                    return -1;
                }
            }
            else if(strcmp(argv[i], "print_all") == 0){
                if(mainArray){
                    printMergedBlocks(mainArray);
                }
                else{
                    printf("Main array has not been created yet!\n");
                    return -1;
                }
            }
        }
    }
    else if(argc == 2){
        if(strcmp(argv[1], "test") == 0){
                runTest();
            }
    }
    else{
        printf("No arguments given!\n");
    }

    if(mainArray){
        for(int i = 0; i < mainArray->size; i++){
            removeBlock(mainArray, i);
        }
        free(mainArray);
    }
}
