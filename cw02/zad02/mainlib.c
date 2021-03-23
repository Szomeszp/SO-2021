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

    FILE *file = NULL;

    if(argc == 1){
        printf("No arguments given!\n");
        printf("You have to specify character and path to file!\n");
        return -1;
    }
    else if(argc == 2){
        printf("Path to file was not specified!\n");
        return -1;
    }
    else{
        file = fopen(argv[2], "r");
    }

    if(file == NULL){
        printf("Error while opening files!\n");
        return -1;
    }

    struct tms start;
    struct tms end;

    times(&start);

    char buf;
    char line[MAX_LINE_SIZE];
    int count;
    int occured;

    while (1){
        count = 0;
        occured = 0;

        while (fread(&buf, sizeof(char), 1, file) == 1 && count < MAX_LINE_SIZE - 2){
            line[count] = buf;
            count = count + 1;
            if(buf == argv[1][0]){
                occured = 1;
            }
            if(buf == '\n'){
                break;
            }
        }

        if(count >= MAX_LINE_SIZE - 2){
            printf("Lines must not have more than 256 characters!\n");
            return -1;
        }

        if(occured){
            fwrite(&line, sizeof(char), count, stdout);
        }

        if (!count){
            break;
        }
    }

    
    times(&end);

    printf("TIME: %f\n", (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

    fclose(file);

    return 0;
}