#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Задача №4. Семинар 4
int main(int argc, char* argv[], char* envp[])
{
  pid_t pid, ppid;
  pid = getpid();
  ppid = getppid();

  fork();

  if(getppid() == pid){
    // Открываем cat для открытия текстового редактора для предыдущего кода.
    (void)execle("/bin/cat", "/bin/cat", "04-1.c", 0, envp);

    // Если неуспешынй вызов:
    printf("Error on program start\n");
    exit(-1);
  }
  else{
    //
  }
 
  return 0;
}