#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
   printf("Uid = %d. Gid = %d\r\n", (int)getuid(), (int)getgid());
   return 0;
}
