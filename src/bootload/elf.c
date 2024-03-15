#include "elf.h"

#include "defines.h"
#include "lib.h"

struct elf_header
{
  struct
  {
    unsigned char magic[4];
    unsigned char class;
    unsigned char format;
    unsigned char version;
    unsigned char abi;
    unsigned char abi_version;
    unsigned char reserve[7];
  } id;
  short type;
  short arch;
  long version;
  long entry_point;
  long program_header_offset;
  long section_header_offset;
  long flags;
  short header_size;
  short program_header_size;
  short program_header_num;
  short section_header_size;
  short section_header_num;
  short section_name_index;
};

struct elf_program_header
{
  long type;
  long offset;
  long virtual_addr;
  long physical_addr;
  long file_size;
  long memory_size;
  long flags;
  long align;
};

// ELFファイルのヘッダをチェック
static int elf_check(struct elf_header * header)
{
  if (memcmp(
        header->id.magic,
        "\x7f"
        "ELF",
        4))
    return -1;

  //ELF32かどうか
  if (header->id.class != 1) return -1;

  //Big Endianかどうか
  if (header->id.format != 2) return -1;

  //バージョンが1かどうか
  if (header->id.version != 1) return -1;

  //実行可能ファイルかどうか
  if (header->type != 2) return -1;

  // versionが1かどうか
  if (header->version != 1) return -1;

  //アーキテクチャがH8/300かH8/300Hかどうか
  if ((header->arch != 46) && (header->arch != 47)) return -1;

  return 0;
}

// セグメント単位でのロード
static int elf_load_program(struct elf_header * header)
{
  int i;
  struct elf_program_header * phdr;
  for (i = 0; i < header->program_header_num; i++) {
    phdr =
      (struct
       elf_program_header *)((char *)header + header->program_header_offset + header->program_header_size * i);
    if (phdr->type != 1) continue;

    // 取り敢えず実際にロードせずにセグメントの情報を表示
    putxval(phdr->offset, 6);
    puts((unsigned char *)" ");
    putxval(phdr->virtual_addr, 8);
    puts((unsigned char *)" ");
    putxval(phdr->physical_addr, 8);
    puts((unsigned char *)" ");
    putxval(phdr->file_size, 5);
    puts((unsigned char *)" ");
    putxval(phdr->memory_size, 5);
    puts((unsigned char *)" ");
    putxval(phdr->flags, 2);
    puts((unsigned char *)" ");
    putxval(phdr->align, 2);
    puts((unsigned char *)"\n");
  }

  return 0;
}

int elf_load(char * buf)
{
  struct elf_header * header = (struct elf_header *)buf;

  if (elf_check(header) < 0) return -1;

  if (elf_load_program(header) < 0) return -1;

  return 0;
}