#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>


int main(int argc, char **argv){
    FILE *dataFile = fopen("dane.txt", "r");

    if(dataFile == NULL){
        printf("Can not open data file!\n");
        return -1;
    }

    FILE *evenFile = fopen("a.txt", "w");
    FILE *tensFile = fopen("b.txt", "w");
    FILE *sqrtFile = fopen("c.txt", "w");
    
    if(evenFile == NULL || tensFile == NULL || sqrtFile == NULL){
        printf("Can not create file!\n");
        if(evenFile){
            fclose(evenFile);
        }
        if(tensFile){
            fclose(tensFile);
        }
        if(sqrtFile){
            fclose(sqrtFile);
        }
        fclose(dataFile);
        return -1;
    }

    struct tms start;
    struct tms end;

    times(&start);

    char line[21];
    int count;
    int flag;

    while (1){
        flag = 0;

        while (fread(&buf, sizeof(char), 1, file) == 1){
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

    fclose(dataFile);
    fclose(evenFile);
    fclose(tensFile);
    fclose(sqrtFile);

    return 0;
}