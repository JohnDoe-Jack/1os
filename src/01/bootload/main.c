#include "defines.h"
#include "lib.h"
#include "serial.h"

int main(void)
{
  serial_init(SERIAL_DEFAULT_DEVICE);
  puts((unsigned char *)"Hello World\n");
  while (1)
    ;
  return 0;
}