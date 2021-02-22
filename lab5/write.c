#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    (void)umask(0);
    
    int fd;

    char name[]="example.fifo";

    // Если создать FIFO невозможно:
    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Невозможно создать FIFO!\n\r");
        exit(-1);
    }

    printf("FIFO был создан\n\r");

    // Пробуем открыть:
    if((fd = open(name, O_WRONLY)) < 0){
        printf("Невозможно открыть FIFO с флагом на запись.\n\r");
        exit(-1);
    }

    // Записываем Hello World из примера:
    size_t size = write(fd, "Hello, world!", 14);

    // Сверяем размер.
    if(size != 14) {
        printf("Произошла ошибка при записи FIFO.\n\r");
        exit(-1);
    }

    // Закрываем поток:
    close(fd);
    
    return 0;
}