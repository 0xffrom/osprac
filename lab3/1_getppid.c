#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    printf("Pid = %d, Ppid = %d", (int)getpid(), (int) getppid());
    return 0;
}