#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>


int main(int argc, char **argv){
    if(argc >= 4){
        printf("Too many arguments!");
        return -1;
    }

    char *pathOne = NULL;
    char *pathTwo = NULL;

    FILE *fileOne = NULL;
    FILE *fileTwo = NULL;

    if(argc == 1){
        printf("Path to first file: \n");
        scanf("%ms", &pathOne);

        printf("Path to second file: \n");
        scanf("%ms", &pathTwo);

        fileOne = fopen(pathOne, "r");
        fileTwo = fopen(pathTwo, "r");

        free(pathOne);
        free(pathTwo);
    }
    else if(argc == 2){
        printf("Path to second file: \n");
        scanf("%ms", &pathTwo);

        fileOne = fopen(argv[1], "r");
        fileTwo = fopen(pathTwo, "r");
        
        free(pathTwo);
    }
    else{
        fileOne = fopen(argv[1], "r");
        fileTwo = fopen(argv[2], "r");
    }

    if(fileOne == NULL || fileTwo == NULL){
        printf("Error while opening files!\n");

        if(fileOne){
            fclose(fileOne);
        }
        if(fileTwo){
            fclose(fileTwo);
        }
        return -1;
    }

    struct tms start;
    struct tms end;

    times(&start);

    char buf;
    int count;

    while (1){
        count = 0;

        while (fread(&buf, sizeof(char), 1, fileOne) == 1){
            count = count + 1;
            fwrite(&buf, sizeof(char), 1, stdout);
            if(buf == '\n'){
                break;
            }
        }

        while (fread(&buf, sizeof(char), 1, fileTwo) == 1){
            count = count + 1;
            fwrite(&buf, sizeof(char), 1, stdout);
            if(buf == '\n'){
                break;
            }
        }
        if (!count){
            break;
        }
    }

    
    times(&end);

    printf("TIME: %f\n", (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

    fclose(fileOne);
    fclose(fileTwo);

    return 0;
}