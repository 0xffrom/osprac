#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

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

    // Флаг F_SETFL указывает, что мы работаем с файлом.
    // Флаг F_GETFD флаг на получение файлового дискриптора.
    // Ставим флаг, чтобы поток не заблокировался.
    // Пример взять в linux
    fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFD | O_NONBLOCK));
    // Результирующее количество System page:
    int result = 0;

    size_t size = 1;
    // Подсчитаем количество system page.
    while(size == 1) {
        size = write(fd[1], resstring, 1);
        
	    if(size != 1){
            // result - количество page
            // sysconf(_SC_PAGESIZE) - размер в байт одного page
            printf("Всего: %d байт\n\r", result * sysconf(_SC_PAGESIZE));
            close(fd[1]);
            exit(-1);
            break;
	    }
        result++;
    }
    return 0;
}
