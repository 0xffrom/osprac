#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
  int     fd;
  size_t  size;

  (void)umask(0);

  // Открываем с O_RDONLY
  if ((fd = open("myfile", O_RDONLY)) < 0) {
    printf("Can\'t open file\n");
    exit(-1);
  }

  // 14 - размер записанной ранее строки.
  char string[14];
  // Читаем:
  size = read(fd, string, 14);

  if (size != 14) {
    printf("Can\'t read all string\n");
    exit(-1);
  }

  // Выводим на экран:
  printf("%s\n\r", string);

  // Закрываем поток:
  if (close(fd) < 0) {
    printf("Can\'t close file\n");
  }

  return 0;
}
