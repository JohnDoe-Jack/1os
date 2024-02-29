PREFIX	= /usr/local
ARCH	= h8300-elf
BINDER	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

AR	= $(BINDER)/$(ADDNAME)ar
AS	= $(BINDER)/$(ADDNAME)as
CC	= $(BINDER)/$(ADDNAME)gcc
LD	= $(BINDER)/$(ADDNAME)ld
NM	= $(BINDER)/$(ADDNAME)nm
OBJCOPY	= $(BINDER)/$(ADDNAME)objcopy
OBJDUMP	= $(BINDER)/$(ADDNAME)objdump
RANLIB	= $(BINDER)/$(ADDNAME)ranlib
STRIP	= $(BINDER)/$(ADDNAME)strip

H8WRITE = ../../tools/h8write/kz_h8write
KZXMODEM = ../../tools/kz_xmodem/kz_xmodem

H8WRITE_SERDEV = /dev/ttyUSB0

OBJS = vector.o startup.o main.o
OBJS += lib.o serial.o xmodem.o

TARGET = kzload# 生成する実行形式のファイル名

CFLAGS = -Wall -mh -nostdlib -fno-builtin
#CFLAGS += -mint32 # int を　32bit にすると掛け算/割り算ができなくなる
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKZLOAD

LFLAGS = -static -T ld.scr -L. # リンクオプション

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all: $(TARGET)

$(TARGET)	:	$(OBJS)
						$(CC) $(OBJS) -o $(TARGET)	$(CFLAGS) $(LFLAGS)
						cp $(TARGET) $(TARGET).elf
						$(STRIP) $(TARGET)

.c.o	:			$<
						$(CC) -c $(CFLAGS) $<

.s.o	:			$<
						$(CC) -c $(CFLAGS) $<

$(TARGET).mot	:	$(TARGET)
						$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot

image	:	$(TARGET).mot

write	:	$(TARGET).mot
				$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

clean	:
				rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot

load : $(KZXMODEM) $(TARGET) $(H8WRITE_SERDEV)