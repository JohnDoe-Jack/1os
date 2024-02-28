#include "defines.h"
#include "lib.h"
#include "serial.h"

static int init(void)
{
  // 以下はリンカスクリプトで定義してあるシンボル
  extern int erodata, data_start, edata, bss_start, ebss;

  // データ領域とBSS領域を初期化
  memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
  memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

  // シリアルの初期化
  serial_init(SERIAL_DEFAULT_DEVICE);

  return 0;
}

int global_data = 0x10;
int global_bss;
static int static_data = 0x20;
static int static_bss;

static void printval(void)
{
  puts((unsigned char *)"global_data = ");
  putxval(global_data, 0);
  puts((unsigned char *)"\n");
  puts((unsigned char *)"global_bss = ");
  putxval(global_bss, 0);
  puts((unsigned char *)"\n");
  puts((unsigned char *)"static_data = ");
  putxval(static_data, 0);
  puts((unsigned char *)"\n");
  puts((unsigned char *)"static_bss = ");
  putxval(static_bss, 0);
  puts((unsigned char *)"\n");
}

int main(void)
{
  init();
  puts((unsigned char *)"Hello World\n");

  printval();
  puts((unsigned char *)"overwrite variables\n");
  global_data = 0x20;
  global_bss = 0x30;
  static_data = 0x40;
  static_bss = 0x50;
  printval();

  while (1)
    ;
  return 0;
}