#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int dataFile = open("dane.txt", O_RDONLY);

    if(dataFile == -1){
        printf("Can not open data file!\n");
        return -1;
    }

    int evenFile = open("a.txt", O_RDONLY);
    int tensFile = open("b.txt", O_RDONLY);
    int sqrtFile = open("c.txt", O_RDONLY);
    
    if(evenFile == -1 || tensFile == -1 || sqrtFile == -1){
        printf("Can not create file!\n");
        if(evenFile == -1){
            close(evenFile);
        }
        if(tensFile == -1){
            close(tensFile);
        }
        if(sqrtFile == -1){
            close(sqrtFile);
        }
        close(dataFile);
        return -1;
    }

    struct tms start;
    struct tms end;

    times(&start);

    char line[256];
    char buf;
    int evenCounter = 0;
    unsigned long long number;
    int count;
 
    while(1){
        count = 0;
        number = 0;

        while (read(dataFile, &buf, sizeof(char)) == 1){
            line[count] = buf;
            count = count + 1;
            if(buf == '\n'){
                line[count] = '\0';
                break;
            }
        }

        if(count >= 21){
            printf("Numbers are too long!\n");
            close(dataFile);
            close(evenFile);
            close(tensFile);
            close(sqrtFile);
            return -1;
        }

        if (!count){
            break;
        }

        if(count > 0){
            sscanf(line, "%llu", &number);
        }

        if(number % 2 == 0){
            evenCounter = evenCounter + 1;
        }

        if((number > 9) && ((number / 10) % 10 == 0 || (number / 10) % 10 == 7)){
            write(tensFile, line, sizeof(char) * count);
        }

        if((unsigned long long)sqrt(number) * (unsigned long long)sqrt(number) == number){
            write(sqrtFile, line, sizeof(char) * count);
        }
    }

    char *txt = "Liczb parzystych jest ";
    sprintf(line, "%d", evenCounter);
    write(evenFile, txt, sizeof(char) * strlen(txt));
    write(evenFile, line, sizeof(char) * strlen(line));

    times(&end);

    printf("TIME: %f\n", (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

    close(dataFile);
    close(evenFile);
    close(tensFile);
    close(sqrtFile);

    return 0;
}