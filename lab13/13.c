#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>

// Делал эту лабу с 22:00 по 23:00 23-го числа, а потом ещё с 8 утра по 13:00. Было интересно, спасибо!

int createFile(char* name){
    FILE* fd = fopen(name, "w");

    if(fd == NULL){
        /* Если файл открыть не удалось, выдаем сообщение об ошибке и завершаем работу */
        printf("File open failed!\n");
       return 1;
    }

    fclose(fd);

    return 0;
}

char* getFileName(int i, int withTemp){
    char* filename = malloc(sizeof("100"));

    if(withTemp == 0){
        sprintf(filename, "temp/%03d", i);
    }
    else{
        sprintf(filename, "%03d", i);
    }

    return filename;
}


int main(int argc, char* argv[]){
    char* directory_name = "temp";

    printf("Looking at the dir: %s\n", directory_name);
    
    DIR *dir = opendir(directory_name);


    // Создайте папку temp.
    if(dir == NULL){
        printf("Error with open directory\n");
        exit(1);
    }

    if(createFile(getFileName(0, 0))){
        /* Если файл открыть не удалось, выдаем сообщение об ошибке и завершаем работу */
        printf("File open failed!\n");
        exit(1);
    }

    int counter = 1;

    while(1){
        char* prevFile = getFileName(counter - 1, 1);
        char* nextFile = getFileName(counter, 0);

        int sym = symlink(prevFile, nextFile);

        if(sym){
            exit(-1);
            return -1;
        }

        if(fopen(nextFile, "r") == NULL){
            printf("%d\n", counter);
            exit(1);
         }

        free(prevFile);
        free(nextFile);

        counter++;
    }

    if (closedir(dir) != 0) {
        printf("Error closing dir!\n");
        return(-1);
    }

    return 0;
}