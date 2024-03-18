#include "defines.h"
#include "lib.h"
#include "serial.h"
static void wait()
{
  volatile long i;
  for (i = 0; i < 300000; i++)
    ;
}

int main(void)
{
  // extern int data_start;
  static unsigned char buf[32];

  // putxval(0x10, 0);
  puts((unsigned char *)"Hello World!\n");
  while (1) {
    puts((unsigned char *)"> ");
    gets((unsigned char *)buf);

    if (!strncmp(buf, (unsigned char *)"echo", 4)) {
      puts(buf + 4);
      puts((unsigned char *)"\n");
    } else if (!strcmp(buf, (unsigned char *)"exit")) {
      break;
    } else {
      puts((unsigned char *)"unknown.\n");
    }
  }
}