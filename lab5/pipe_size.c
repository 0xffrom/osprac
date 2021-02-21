#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
    // Выделяем pipe:
    int fd[2];
    // Выделяем 1 байт:
    char* resstring = malloc(1 * sizeof(char));
    // Если pipe < 0, значит не удалось создать pipe.
    if(pipe(fd) < 0){
        printf("Невозможно создать pipe\n\r");
        exit(-1);
    }

    // Флаг F_SETFL указывает, что мы работаем с файлом
    // Флаг F_GETFD флаг на получение файлового дескриптора.
    // Пример взят с linuxlib.ru 
    fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFD | O_NONBLOCK));

    // Результирующее количество байт:
    int result = 0;

    size_t size = 1;
    // Записывам по 1 байту и инкрементируем счётчик
    while(size == 1){
        size = write(fd[1], resstring, 1);
        result++;
    }

    printf("Всего: %d байт\n\r", result);
    return 0;
}