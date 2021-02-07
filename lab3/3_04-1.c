#include <stdio.h>

// Задача №3. Семинар 4
int main(int argc, char *argv[], char *envp[]){
    printf("Количество аргументов командной строки: %d\n\r", argc);
    printf("Аргументы командной строки: ");

    for (int i = 0; i < argc; i++)
    {
        if(i != argc - 1){
            printf("%s, ", argv[i]);
        }
        else{
            printf("%s.\n\r", argv[i]);
        }
    }
    
    printf("Параметры окружающей среды:\n");
    int i = 0;
    while (envp[i] != NULL){
        printf("%s\n", envp[i++]);
    }

    printf("\n");

    return 0;
}