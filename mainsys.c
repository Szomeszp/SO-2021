#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){
    if(argc >= 4){
        printf("Too many arguments!");
        return -1;
    }

    char *pathOne = NULL;
    char *pathTwo = NULL;

    int fileOne = -1;
    int fileTwo = -1;

    if(argc == 1){
        printf("Path to first file: \n");
        scanf("%ms", &pathOne);

        printf("Path to second file: \n");
        scanf("%ms", &pathTwo);

        fileOne = open(pathOne, O_RDONLY);
        fileTwo = open(pathTwo, O_RDONLY);

        free(pathOne);
        free(pathTwo);
    }
    else if(argc == 2){
        printf("Path to second file: \n");
        scanf("%ms", &pathTwo);

        fileOne = open(argv[1], O_RDONLY);
        fileTwo = open(pathTwo, O_RDONLY);
        
        free(pathTwo);
    }
    else{
        fileOne = open(argv[1], O_RDONLY);
        fileTwo = open(argv[2], O_RDONLY);
    }

    if(fileOne == -1 || fileTwo == -1){
        printf("Error while opening files!\n");
        
        if(fileOne){
            close(fileOne);
        }
        if(fileTwo){
            close(fileTwo);
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

        while (read(fileOne, &buf, sizeof(char)) == 1){
            count = count + 1;
            write(STDOUT_FILENO, &buf, sizeof(char));
            if(buf == '\n'){
                break;
            }
        }

        while (read(fileTwo, &buf, sizeof(char)) == 1){
            count = count + 1;
            write(STDOUT_FILENO, &buf, sizeof(char));
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

    close(fileOne);
    close(fileTwo);

    return 0;
}