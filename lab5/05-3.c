#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void reverse(char* str, size_t sz);

int main()
{
    int parent[2], child[2], result;
    size_t size;
    char resstring[14];

    // Создаём Pipes родителя и ребёнка:
    if (pipe(parent) < 0) {
        printf("Невозможно создать pipe отца\n\r");
        exit(-1);
    }

    if (pipe(child) < 0) {
        printf("Невозможно создать pipe ребёнка\n\r");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Неудачный fork\n\r");
        exit(-1);
    } else if (result > 0) {
        // Отец
        // Закрываем на чтение отца
        close(parent[0]);
        // Закрываем на запись ребёнка.
        close(child[1]);
        // Пишем HelloWorld в отца.
        size = write(parent[1], "Hello, world!", 14);
        // P.s обработка ошибок как в примере.
        if (size != 14) {
            printf("Can\'t write all string\n\r");
            exit(-1);
        }
        // Закрываем запись отца.
        close(parent[1]);

        // Читаем ребёнка:
        size = read(child[0], resstring, 14);
        if (size != 14) {
            printf("Can\'t read from child\n\r");
            exit(-1);
        }

        close(child[0]);
        printf("Отец прочитал с ребёнка: %s\n\rОтец закончил.\n\r", resstring);
    } else {
        // Ребёнок
        // Закрывем на запись отца:
        close(parent[1]);
        // Закрываем на чтение ребёнка.
        close(child[0]);
        // Читаем отца:
        size = read(parent[0], resstring, 14);
        if (size < 0) {
            printf("Can\'t get from parent\n\r");
            exit(-1);
        }
        // Печатаем, что прочитали:
        printf("Ребёнок получил с отца: %s\n\r", resstring);
        // Запишем ребёнком, что прочитали:
        size = write(child[1], resstring, 14);
        // Закроем потоки
        close(child[1]);
        close(parent[0]);
        printf("Ребёнок вышел\n\r");
    }
    return 0;
}
