#include "lib.h"

#include "defines.h"
#include "serial.h"

// Send a character to the serial port
int putc(unsigned char c)
{
  if (c == '\n') serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
  return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

// Send a string to the serial port
int puts(unsigned char * str)
{
  while (*str) putc(*(str++));

  return 0;
}