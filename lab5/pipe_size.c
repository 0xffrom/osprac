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

    // Результирующее количество байт:
    int result = 0;

    size_t size = 1;
    // Записывам по 1 байту и инкрементируем счётчик
    while(size == 1 && result < 65536) {
        // Операция write заблокируется как только pipe достигнет предела.
        // В моём случае это 65536 байт.
        size = write(fd[1], resstring, 1);
        
	    if(size != 1){
            close(fd[1]);
            exit(-1);
            break;
	    }
        result++;
    }

    printf("Всего: %d байт\n\r", result);
    return 0;
}
