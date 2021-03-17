#include "merge.h"

char *generateRandomLine(){

    const int SIZE = (rand() % 10) + 20;
    const char* CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz";

    const size_t NUMBER_OF_CHARS = strlen(CHARACTERS);

    char* result = (char*)malloc(SIZE + 2 * sizeof(char));

    for(int i = 0; i < SIZE; i++){
        result[i] = CHARACTERS[rand() % NUMBER_OF_CHARS];
    }
    result[SIZE] = '\n';
    result[SIZE + 1] = '\0';

    return result;
}

void generateFile(char* fileName, int numOfRows){
    FILE* file = fopen(fileName, "w+");
    char* buff;
    for(int i = 0; i < numOfRows; i++){
        buff = generateRandomLine();
        fprintf(file, "%s", buff);
        free(buff);
    }
    fclose(file);
}


int main(int argc, char **argv){
    mainArray_t *mainArray = NULL;

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
                if(mainArray){
                    printMergedBlocks(mainArray);
                }
                else{
                    printf("Main array has not been created yet!\n");
                    return -1;
                }
            }
    }
    else{
        printf("No arguments given!\n");
    }
}
