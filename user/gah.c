#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int gen_and_hold(char *filename)
{
  int fd = open(filename, O_CREATE | O_RDWR);
  return fd;
}

void work(const char *dir, int gen_cnt)
{
  char filename[20];
  memset(filename, 20, sizeof(char));
  strcpy(filename, dir);
  uint len = strlen(filename);
  filename[len] = '/';

  // printf("[GAH] Gen and hold files\n");
  for (int i = 0; i < gen_cnt; ++i)
  {
    filename[len + 1] = '0' + i / 100;
    filename[len + 2] = '0' + (i / 10) % 10;
    filename[len + 3] = '0' + i % 10;
    gen_and_hold(filename);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("gen_and_hold <dir> <num> - generate and hold files\n");
    exit(0);
  }

  printf("%d", getpid());

  char buf[512];
  int n;

  while ((n = read(0, buf, sizeof(buf))) > 0)
  {
    if (!strcmp(buf, "Ok"))
    {
      break;
    }
  }

  work(argv[1], atoi(argv[2]));

  printf("Ok");

  while (1)
    ;

  exit(0);
}
