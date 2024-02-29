#ifndef _SERIAL_H_INCLUDED
#define _SERIAL_H_INCLUDED

int serial_init(int index);     // initialize device
int serial_is_send_enable(int index); // check if send action is enable
int serial_send_byte(int index,unsigned char b);  // send a byte

#endif