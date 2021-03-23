#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

#define MAX_LINE_SIZE 256

int main(int argc, char **argv){
    if(argc >= 4){
        printf("Too many arguments!\n");
        return -1;
    }

    FILE *fileRead = NULL;
    FILE *fileWrite = NULL;

    if(argc == 1){
        printf("No arguments given!\n");
        printf("You have to specify paths to files!\n");
        return -1;
    }
    else if(argc == 2){
        printf("Path to saving file was not specified!\n");
        return -1;
    }
    else{
        fileRead = fopen(argv[1], "r");
        fileWrite = fopen(argv[2], "w");
    }

    if(fileRead == NULL || fileWrite == NULL){
        printf("Error while opening files!\n");
        if(fileRead){
            fclose(fileRead);
        }
        if(fileWrite){
            fclose(fileWrite);
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

        while (fread(&buf, sizeof(char), 1, fileRead) == 1){
            if(count == 0 && buf == '\n'){
                count = count + 1;
                break;
            }
            fwrite(&buf, sizeof(char), 1, fileWrite);
            count = count + 1;
            if(count == 50){
                if(buf != '\n'){
                    fwrite("\n", sizeof(char), 1, fileWrite);
                }
                break;
            }
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

    fclose(fileRead);
    fclose(fileWrite);

    return 0;
}