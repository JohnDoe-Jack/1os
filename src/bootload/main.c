#include "defines.h"
#include "elf.h"
#include "lib.h"
#include "serial.h"
#include "xmodem.h"

static int init(void)
{
  // 以下はリンカスクリプトで定義してあるシンボル
  extern int data_start_load, data_start, edata, bss_start, ebss;

  // データ領域とBSS領域を初期化
  memcpy(&data_start, &data_start_load, (long)&edata - (long)&data_start);
  memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

  // シリアルの初期化
  serial_init(SERIAL_DEFAULT_DEVICE);

  return 0;
}

static int dump(unsigned char * buf, long size)
{
  long i;

  if (size < 0) {
    puts((unsigned char *)"no data.\n");
    return -1;
  }

  for (i = 0; i < size; i++) {
    putxval(buf[i], 2);
    if ((i & 0xf) == 15) {
      puts((unsigned char *)"\n");
    } else {
      if ((i & 0xf) == 7) puts((unsigned char *)" ");
      puts((unsigned char *)" ");
    }
  }
  puts((unsigned char *)"\n");

  return 0;
}

static void wait()
{
  volatile long i;
  for (i = 0; i < 300000; i++)
    ;
}

int main(void)
{
  static unsigned char buf[16];
  static long size = -1;
  static unsigned char * loadbuf = NULL;
  char * entry_point;
  void (*f)(void);
  extern int buffer_start;  // リンカスクリプトで定義されるバッファ

  init();

  puts((unsigned char *)"kzload (kozos boot loader) started.\n");

  while (1) {
    puts((unsigned char *)"kzload> ");
    gets(buf);

    if (!strcmp(buf, (unsigned char *)"load")) {  // XMODEMでのファイルのダウンロード
      loadbuf = (unsigned char *)(&buffer_start);
      size = xmodem_recv(loadbuf);
      wait();
      if (size < 0) {
        puts((unsigned char *)"\nXMODEM receive error!\n");
      } else {
        puts((unsigned char *)"\nXMODEM receive succeeded.\n");
      }
    } else if (!strcmp(buf, (unsigned char *)"dump")) {  // メモリの16進ダンプ出力
      puts((unsigned char *)"size: ");
      putxval(size, 0);
      puts((unsigned char *)"\n");
      dump(loadbuf, size);
    } else if (!strcmp(buf, (unsigned char *)"run")) {  // ELF形式ファイルの実行
      entry_point = elf_load(loadbuf);                  // メモリ上に展開
      if (!entry_point) {
        puts((unsigned char *)"run error!\n");
      } else {
        puts((unsigned char *)"starting from entry point: ");
        putxval((unsigned long)entry_point, 0);
        puts((unsigned char *)"\n");
        f = (void (*)(void))entry_point;
        f();  // 関数呼び出し
        /* ここには返ってこない*/
      }
    } else {
      puts((unsigned char *)"unknown.\n");
    }
  }
  while (1)
    ;
  return 0;
}