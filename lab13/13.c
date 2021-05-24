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

// Получаем указатель на название файла в папке temp или без неё.
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

void mFree(char* f1, char* f2){
    free(f1);
    free(f2);
}

// Папка temp создаётся через system.

int main(int argc, char* argv[]){
    char* directory_name = "temp";

    printf("Looking at the dir: %s\n", directory_name);
    
    DIR *dir = opendir(directory_name);

    // Проверка на папку temp:
    if(dir != NULL){
        // Если папка есть - значит удаляем её и все файлы внутри.
       system("rm -r temp");
    }

    // Создать папку temp, её либо не было, либо удалили
    system("mkdir temp");

    char* firstName = getFileName(0, 0);
    if(createFile(firstName)){
        /* Если файл открыть не удалось, выдаем сообщение об ошибке и завершаем работу */
        free(firstName);
        printf("File open failed!\n");
        exit(1);
    }

    free(firstName);

    int counter = 1;

    while(1){
        char* prevFile = getFileName(counter - 1, 1);
        char* nextFile = getFileName(counter, 0);

        if(symlink(prevFile, nextFile)) {
            mFree(prevFile, nextFile);

            printf("Symlink error\n");
            exit(-1);
        }

        
        // Пытаемся открыть файл и определить, корректная ссылка или нет
        // если битая ссылка, то вылезет Null
        FILE* newFile = fopen(nextFile, "r");
        if(newFile == NULL){
            // ПОСЛЕДНИЙ ФАЙЛ НЕ УЧИТЫВАЕМ.
            printf("%d\n", counter - 1);

            mFree(prevFile, nextFile);

            exit(1);
         }

        fclose(newFile);
        mFree(prevFile, nextFile);

        counter++;
    }

    if (closedir(dir) != 0) {
        printf("Error closing dir!\n");
        return(-1);
    }

    return 0;
}