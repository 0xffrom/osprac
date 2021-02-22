
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Мы должны скомпилить read.c и write.c в два разных файла.
 * И запускать их по отдельности. Сначала read.c, потом write.c
 */ 
int main()
{
    // Название файла:
    char name[] = "example.fifo";

    (void)umask(0);

    // Если создать FIFO невозможно:
    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Невозможно создать FIFO!\n\r");
        exit(-1);
    }

    printf("FIFO был создан\n\r");

    int fd;
    // Пробуем прочитать:
    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Невозможно прочитать FIFO \n\r");
        exit(-1);
    }

    size_t size;
    // Выделяем память под текст:
    char resstring[14];
    // Читаем: 
    size = read(fd, resstring, 14);
    if (size < 0) {
        printf("Неудачное чтение.\n\r");
        exit(-1);
    }

    // Прочитанная строка:
    printf("Результат чтения FIFO: %s\n\r", resstring);

    // Закрываем поток:
    close(fd);
    return 0;
}