#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include "stdlib.h"
#include <sys/shm.h>
#include <sys/ipc.h>

int main()
{
    // IPC дескриптор для области в памяти:
    int shmid;
    // Путь к файлу для чтения:
    char pathname[] = "7-print.c";
    // IPC ключ
    key_t key;

    FILE *file;
    // Открываем файл:
    file = fopen(pathname, "r");
    
    fseek(file, 0L, SEEK_END);

    // Размер файла
    int file_size = 0;
    file_size = ftell(file);
    rewind(file);
    
    // Генерируем ключ
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    // Пытаем отобразить разделяемую память:
    if ((shmid = shmget(key, sizeof(int) + file_size * sizeof(char), 0666|IPC_CREAT)) < 0) {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }

    int *file_size_ptr;

    if ((file_size_ptr = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    *file_size_ptr = file_size;

    // Строка для хранения файла
    char *source_code;
    // Вычисляем размер для строки:
    source_code = (char*)(file_size_ptr + 1);
    
    // Копируем символы:
    for (int i = 0; i < file_size; ++i){
        source_code[i] = fgetc(file);
    }
        
    // Закрываем поток:
    fclose(file);
        
    // Удаляем разделяемую память из адресного пространства текущего
    // процесса и завершаем работу:
    if (shmdt(file_size_ptr) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}