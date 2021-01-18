#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
   printf("Pid = %d. Ppid = %d\r\n", (int)getpid(), (int)getppid());
   return 0;
}
