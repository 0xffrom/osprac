#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>

int inc(int semid, struct sembuf* buf) {
    buf->sem_op = 1;
    buf->sem_flg = 0;
    buf->sem_num = 0;

    return semop(semid, buf, 1);
}

int dec(int semid, struct sembuf* buf) {
    buf->sem_op = -1;
    buf->sem_flg = 0;
    buf->sem_num = 0;

    return semop(semid, buf, 1);
}

int main()
{
    int parent[2], result;
    size_t size = 0;
    key_t key;
    char pathname[] = "05-3.c";
    struct sembuf mybuf;

    int N;
    printf("������� N: \n");
    scanf("%d", &N);
    char resstring[14 * N];

    if (N <= 2) {
        printf("N ������ ���� ������ 2.\n");
        exit(-1);
    }

    // ������ Pipes �������� � ������:
    if (pipe(parent) < 0) {
        printf("���������� ������� pipe ����\n\r");
        exit(-1);
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("���� �� ������������.\n");
        exit(-1);
    }

    // ������ ����������
    if ((semid = semget(key, 1, 0666)) < 0) {
        printf("������� �� ������, ��������: \n");
        if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
            printf("�� ���� �������� Semid\n");
            exit(-1);
        }
        printf("������� ������!\n");
    }

    result = fork();

    if (result < 0) {
        printf("��������� fork\n\r");
        exit(-1);
    }

    else if (result > 0) {
        for (int i = 0; i < N; ++i) {
            size += write(parent[1], "Hello, world!", 14);
        }
        
        // P.s ��������� ������ ��� � �������.
        if (size != 14 * N) {
            printf("Can\'t write all string\n\r");
            exit(-1);
        }
        
        // ��� ������:
        dec(semid, &mybuf); 

        // ������ ������:
        size = read(child[0], resstring, 14 * N);
        if (size != 14 * N) {
            printf("Can\'t read from child\n\r");
            exit(-1);
        }

        close(child[0]);
        printf("���� �������� � ������: %s\n\r���� ��������.\n\r", resstring);
    }
    else {
        // ������

        // ������ ����:
        size = read(parent[0], resstring, 14 * N);
        if (size < 0) {
            printf("Can\'t get from parent\n\r");
            exit(-1);
        }
        // ��������, ��� ���������:
        printf("������ ������� � ����: %s\n\r", resstring);
        // ������� �������, ��� ���������:
        size = write(parent[1], resstring, 14 * N);

        // �����:
        inc(semid, &mybuf); 

        if (size != 14 * N) {
            printf("���������� �������� ��� ������.\n");
            exit(-1);
        }
        else {
            printf("�� ��� ���.\n");
        }

        close(parent[1]);
        close(parent[0]);
        printf("������ �����\n\r");
    }
    return 0;
}