#ifndef _LTB_H_INCLUDED
#define _LTB_H_INCLUDED

int putc(unsigned char c);      // one character output
int puts(unsigned char * str);  // string output
void * memset(void * b, int c, long len);
void * memcpy(void * dst, const void * b2, long len);
int memcmp(const void * b1, const void * b2, long len);
int strlen(const char * s);
char * strcpy(char * dst, const char * src);
int strcmp(const char * s1, const char * s2);
int strncmp(const char * s1, const char * s2, int len);
int putxval(unsigned long value, int column);

#endif