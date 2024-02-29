#ifndef _LTB_H_INCLUDED
#define _LTB_H_INCLUDED

int putc(unsigned char c);      // one character output
unsigned char getc(void);       // one character input
int puts(unsigned char * str);  // string output
int gets(unsigned char * buf);  // string input
void * memset(void * b, int c, long len);
void * memcpy(void * dst, const void * b2, long len);
int memcmp(const void * b1, const void * b2, long len);
int strlen(const char * s);
char * strcpy(char * dst, const char * src);
int strcmp(const unsigned char * s1, const unsigned char * s2);
int strncmp(const unsigned char * s1, const unsigned char * s2, int len);
int putxval(unsigned long value, int column);

#endif