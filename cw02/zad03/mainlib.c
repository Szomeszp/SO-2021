#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

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

    char line[256];
    char buf;
    int evenCounter = 0;
    unsigned long long number;
    int count;
 
    while(1){
        count = 0;
        number = 0;

        while (fread(&buf, sizeof(char), 1, dataFile) == 1){
            line[count] = buf;
            count = count + 1;
            if(buf == '\n'){
                line[count] = '\0';
                break;
            }
        }

        if(count >= 21){
            printf("Numbers are too long!\n");
            fclose(dataFile);
            fclose(evenFile);
            fclose(tensFile);
            fclose(sqrtFile);
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
            fwrite(line, sizeof(char), count, tensFile);
        }

        if((unsigned long long)sqrt(number) * (unsigned long long)sqrt(number) == number){
            fwrite(line, sizeof(char), count, sqrtFile);
        }
    }

    char *txt = "Liczb parzystych jest ";
    sprintf(line, "%d", evenCounter);
    fwrite(txt, sizeof(char), strlen(txt), evenFile);
    fwrite(line, sizeof(char), strlen(line), evenFile);

    times(&end);

    printf("TIME: %f\n", (double)(end.tms_stime - start.tms_stime)/sysconf(_SC_CLK_TCK));

    fclose(dataFile);
    fclose(evenFile);
    fclose(tensFile);
    fclose(sqrtFile);

    return 0;
}