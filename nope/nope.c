#include <stddef.h>
#include <elf.h>

#define ADDR_RODATA 0x00400000

enum sections
{
  SHN_INTERP = 1, SHN_HASH, SHN_GNU_HASH, SHN_DYNSYM, SHN_DYNSTR, SHN_TEXT,
  SHN_EH_FRAME, SHN_DYNAMIC, SHN_DATA, SHN_SYMTAB, SHN_STRTAB, SHN_SHSTRTAB,
  SHN_COUNT
};

typedef struct elf
{
  Elf64_Ehdr      ehdr;
  Elf64_Phdr      phdrs[8];
  unsigned char   interp[28];
  unsigned char   pad1[4];
  Elf64_Word      hash[4];
  Elf64_Word      gnu_hash[7];
  unsigned char   pad2[4];
  Elf64_Sym       dynsym[1];
  char            dynstr[11];
  unsigned char   pad3[3469];
  unsigned char   text[318];
  unsigned char   pad4[7650];
  Elf64_Dyn       dynamic[14];
  unsigned char   data[82];
  unsigned char   pad5[6];
  Elf64_Sym       symtab[36];
  char            strtab[222];
  char            shstrtab[92];
  unsigned char   pad6[6];
  Elf64_Shdr      shdrs[SHN_COUNT];
} elf;

elf foo =
{
  /* ehdr */
  {
    { 0x7F, 'E', 'L', 'F', ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV,
      0, 0, 0, 0, 0, 0, 0, 0 },
    ET_EXEC, EM_X86_64, EV_CURRENT, ADDR_RODATA + offsetof(elf, text),
    offsetof(elf, phdrs), offsetof(elf, shdrs), 0, sizeof(Elf64_Ehdr),
    sizeof(Elf64_Phdr), sizeof foo.phdrs / sizeof *foo.phdrs,
    sizeof(Elf64_Shdr), sizeof foo.shdrs / sizeof *foo.shdrs, SHN_SHSTRTAB
  },
  /* phdrs */
  {
    { PT_PHDR, PF_R, offsetof(elf, phdrs), ADDR_RODATA + offsetof(elf, phdrs),
      ADDR_RODATA + offsetof(elf, phdrs), sizeof foo.phdrs, sizeof foo.phdrs,
      sizeof(Elf64_Addr) },
    { PT_INTERP, PF_R, offsetof(elf, interp),
      ADDR_RODATA + offsetof(elf, interp),
      ADDR_RODATA + offsetof(elf, interp), sizeof foo.interp,
      sizeof foo.interp, 1 },
    { PT_LOAD, PF_R, 0, ADDR_RODATA, ADDR_RODATA, offsetof(elf, pad3),
      offsetof(elf, pad3), 0x1000 },
    { PT_LOAD, PF_R | PF_X, offsetof(elf, text),
      ADDR_RODATA + offsetof(elf, text), ADDR_RODATA + offsetof(elf, text),
      sizeof foo.text, sizeof foo.text, 0x1000 },
    { PT_LOAD, PF_R, offsetof(elf, pad4) + 0x0EC2,
      ADDR_RODATA + offsetof(elf, pad4) + 0x0EC2,
      ADDR_RODATA + offsetof(elf, pad4) + 0x0EC2, 0, 0, 0x1000 },
    { PT_LOAD, PF_R | PF_W, offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic),
      offsetof(elf, pad5) - offsetof(elf, dynamic),
      offsetof(elf, pad5) - offsetof(elf, dynamic), 0x1000 },
    { PT_DYNAMIC, PF_R | PF_W, offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic), sizeof foo.dynamic,
      sizeof foo.dynamic, sizeof(Elf64_Addr) },
    { PT_GNU_RELRO, PF_R, offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic),
      ADDR_RODATA + offsetof(elf, dynamic), sizeof foo.dynamic,
      sizeof foo.dynamic, 1 }
  },
  /* interp */
  "/lib64/ld-linux-x86-64.so.2",
  /* pad1 */
  { 0 },
  /* hash */
  {
    1, 1,
    0,
    0
  },
  /* gnu_hash */
  {
    1, 1, 1, 0,
    0x00000000, 0x00000000,
    0
  },
  /* pad2 */
  { 0 },
  /* dynsym */
  {
    { 0, 0, 0, SHN_UNDEF, 0, 0 }
  },
  /* dynstr */
  "\0libc.so.6",
  /* pad3 */
  { 0 },
  /* text */
  {
    0xE8, 0x05, 0x00, 0x00, 0x00, 0xE9, 0x28, 0x01, 0x00, 0x00, 0x90, 0xB8,
    0x04, 0x00, 0x00, 0x00, 0xBB, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90,
    0x48, 0x8D, 0x0C, 0x25, 0x00, 0x30, 0x40, 0x00, 0x90, 0x90, 0xBA, 0x03,
    0x00, 0x00, 0x00, 0xCD, 0x80, 0x90, 0xB8, 0x04, 0x00, 0x00, 0x00, 0x90,
    0x90, 0xBB, 0x01, 0x00, 0x00, 0x00, 0x90, 0x48, 0x8D, 0x0C, 0x25, 0x03,
    0x30, 0x40, 0x00, 0xBA, 0x03, 0x00, 0x00, 0x00, 0x90, 0xCD, 0x80, 0xB8,
    0x04, 0x00, 0x00, 0x00, 0xBB, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90, 0x48,
    0x8D, 0x0C, 0x25, 0x06, 0x30, 0x40, 0x00, 0xBA, 0x03, 0x00, 0x00, 0x00,
    0x90, 0xCD, 0x80, 0x90, 0x90, 0xB8, 0x04, 0x00, 0x00, 0x00, 0x90, 0xBB,
    0x01, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0C, 0x25, 0x09, 0x30, 0x40, 0x00,
    0x90, 0xBA, 0x03, 0x00, 0x00, 0x00, 0xCD, 0x80, 0xB8, 0x04, 0x00, 0x00,
    0x00, 0x90, 0x90, 0xBB, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0C, 0x25,
    0x0C, 0x30, 0x40, 0x00, 0xBA, 0x03, 0x00, 0x00, 0x00, 0x90, 0xCD, 0x80,
    0x90, 0x90, 0x90, 0xB8, 0x04, 0x00, 0x00, 0x00, 0xBB, 0x01, 0x00, 0x00,
    0x00, 0x90, 0x48, 0x8D, 0x0C, 0x25, 0x0F, 0x30, 0x40, 0x00, 0x90, 0x90,
    0x90, 0x90, 0xBA, 0x03, 0x00, 0x00, 0x00, 0xCD, 0x80, 0x90, 0x90, 0xB8,
    0x04, 0x00, 0x00, 0x00, 0x90, 0xBB, 0x01, 0x00, 0x00, 0x00, 0x90, 0x48,
    0x8D, 0x0C, 0x25, 0x12, 0x30, 0x40, 0x00, 0xBA, 0x03, 0x00, 0x00, 0x00,
    0x90, 0xCD, 0x80, 0xB8, 0x04, 0x00, 0x00, 0x00, 0xBB, 0x01, 0x00, 0x00,
    0x00, 0x90, 0x90, 0x48, 0x8D, 0x0C, 0x25, 0x15, 0x30, 0x40, 0x00, 0xBA,
    0x03, 0x00, 0x00, 0x00, 0x90, 0xCD, 0x80, 0xB8, 0x04, 0x00, 0x00, 0x00,
    0xBB, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8D, 0x0C, 0x25, 0x18, 0x30, 0x40,
    0x00, 0x90, 0xBA, 0x03, 0x00, 0x00, 0x00, 0xCD, 0x80, 0xB8, 0x04, 0x00,
    0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0xBB, 0x01, 0x00, 0x00, 0x00,
    0x48, 0x8D, 0x0C, 0x25, 0x1B, 0x30, 0x40, 0x00, 0xBA, 0x03, 0x00, 0x00,
    0x00, 0x90, 0x90, 0xCD, 0x80, 0xC3, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xBB,
    0x00, 0x00, 0x00, 0x00, 0xCD, 0x80
  },
  /* pad4 */
  { 0 },
  /* dynamic */
  {
    { DT_NEEDED, { 1 } }, /* libc.so.6 */
    { DT_HASH, { ADDR_RODATA + offsetof(elf, hash) } },
    { DT_GNU_HASH, { ADDR_RODATA + offsetof(elf, gnu_hash) } },
    { DT_STRTAB, { ADDR_RODATA + offsetof(elf, dynstr) } },
    { DT_SYMTAB, { ADDR_RODATA + offsetof(elf, dynsym) } },
    { DT_STRSZ, { sizeof foo.dynstr } },
    { DT_ADDRNUM, { sizeof(Elf64_Sym) } },
    { DT_DEBUG, { 0 } },
    { DT_NULL, { 0 } },
    { DT_NULL, { 0 } },
    { DT_NULL, { 0 } },
    { DT_NULL, { 0 } },
    { DT_NULL, { 0 } },
    { DT_NULL, { 0 } }
  },
  /* data */
  "La clave no es flag{ASM} }:)\n\0L\0a\0 \0f\0l\0a\0g\0 \0n\0o\0 \0e\0s\0 \0"
    "f\0l\0a\0g\0{\0a\0s\0m\0}\0 \0}:)",
  /* pad5 */
  { 0 },
  /* symtab */
  {
    { 0, 0, 0, SHN_UNDEF, 0, 0 },
    /* the.asm */
    { 1, ELF64_ST_INFO(STB_LOCAL, STT_FILE), STV_DEFAULT, SHN_ABS, 0, 0 },
    /* flag */
    { 179, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data), 0 },
    /* flag1 */
    { 9, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x1E, 0 },
    /* flag2 */
    { 15, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x20, 0 },
    /* flag3 */
    { 21, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x22, 0 },
    /* flag4 */
    { 27, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x24, 0 },
    /* flag5 */
    { 33, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x26, 0 },
    /* flag6 */
    { 39, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x28, 0 },
    /* flag7 */
    { 45, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x2A, 0 },
    /* flag8 */
    { 51, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x2C, 0 },
    /* flag9 */
    { 57, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x2E, 0 },
    /* flag10 */
    { 63, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x30, 0 },
    /* flag11 */
    { 70, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x32, 0 },
    /* flag12 */
    { 77, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x34, 0 },
    /* flag13 */
    { 84, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x36, 0 },
    /* flag14 */
    { 91, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x38, 0 },
    /* flag15 */
    { 98, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x3A, 0 },
    /* flag16 */
    { 105, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x3C, 0 },
    /* flag17 */
    { 112, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x3E, 0 },
    /* flag18 */
    { 119, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x40, 0 },
    /* flag19 */
    { 126, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x42, 0 },
    /* flag20 */
    { 133, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x44, 0 },
    /* flag21 */
    { 140, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x46, 0 },
    /* flag22 */
    { 147, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x48, 0 },
    /* flag23 */
    { 154, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x4A, 0 },
    /* flag24 */
    { 161, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x4C, 0 },
    /* flag25 */
    { 168, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, data) + 0x4E, 0 },
    /* the_flag */
    { 175, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_RODATA + offsetof(elf, text) + 10, 0 },
    /* end */
    { 201, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_RODATA + offsetof(elf, text) + 0x0132, 0 },
    { 0, ELF64_ST_INFO(STB_LOCAL, STT_FILE), STV_DEFAULT, SHN_ABS, 0, 0 },
    /* _DYNAMIC */
    { 184, ELF64_ST_INFO(STB_LOCAL, STT_OBJECT), STV_DEFAULT, SHN_DYNAMIC,
      ADDR_RODATA + offsetof(elf, dynamic), 0 },
    /* _edata */
    { 193, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, pad5), 0 },
    /* _end */
    { 200, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      0x403058, 0 },
    /* __bss_start */
    { 205, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_RODATA + offsetof(elf, pad5), 0 },
    /* main */
    { 217, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_RODATA + offsetof(elf, text), 0 }
  },
  /* strtab */
  "\0the.asm\0flag1\0flag2\0flag3\0flag4\0flag5\0flag6\0flag7\0flag8\0flag9\0"
    "flag10\0flag11\0flag12\0flag13\0flag14\0flag15\0flag16\0flag17\0flag18\0"
    "flag19\0flag20\0flag21\0flag22\0flag23\0flag24\0flag25\0the_flag\0_DYNA"
    "MIC\0_edata\0_end\0__bss_start\0main",
  /* shstrtab */
  "\0.symtab\0.strtab\0.shstrtab\0.interp\0.gnu.hash\0.dynsym\0.dynstr\0.tex"
    "t\0.eh_frame\0.dynamic\0.data",
  /* pad6 */
  { 0 },
  /* shdrs */
  {
    { 0, SHT_NULL, 0, 0, 0, 0, SHN_UNDEF, 0, 0, 0 },
    /* .interp */
    { 27, SHT_PROGBITS, SHF_ALLOC, ADDR_RODATA + offsetof(elf, interp),
      offsetof(elf, interp), sizeof foo.interp, SHN_UNDEF, 0, 1, 0 },
    /* .hash */
    { 39, SHT_HASH, SHF_ALLOC, ADDR_RODATA + offsetof(elf, hash),
      offsetof(elf, hash), sizeof foo.hash, SHN_DYNSYM, 0, sizeof(Elf64_Addr),
      sizeof(Elf64_Word) },
    /* .gnu.hash */
    { 35, SHT_GNU_HASH, SHF_ALLOC, ADDR_RODATA + offsetof(elf, gnu_hash),
      offsetof(elf, gnu_hash), sizeof foo.gnu_hash, SHN_DYNSYM, 0,
      sizeof(Elf64_Addr), 0 },
    /* .dynsym */
    { 45, SHT_DYNSYM, SHF_ALLOC, ADDR_RODATA + offsetof(elf, dynsym),
      offsetof(elf, dynsym), sizeof foo.dynsym, SHN_DYNSTR, 1,
      sizeof(Elf64_Addr), sizeof(Elf64_Sym) },
    /* .dynstr */
    { 53, SHT_STRTAB, SHF_ALLOC, ADDR_RODATA + offsetof(elf, dynstr),
      offsetof(elf, dynstr), sizeof foo.dynstr, SHN_UNDEF, 0, 1, 0 },
    /* .text */
    { 61, SHT_PROGBITS, SHF_EXECINSTR | SHF_ALLOC,
      ADDR_RODATA + offsetof(elf, text), offsetof(elf, text), sizeof foo.text,
      SHN_UNDEF, 0, 0x10, 0 },
    /* .eh_frame */
    { 67, SHT_PROGBITS, SHF_ALLOC, ADDR_RODATA + offsetof(elf, pad4) + 0x0EC2,
      offsetof(elf, pad4) + 0x0EC2, 0, SHN_UNDEF, 0, sizeof(Elf64_Addr), 0 },
    /* .dynamic */
    { 77, SHT_DYNAMIC, SHF_WRITE | SHF_ALLOC,
      ADDR_RODATA + offsetof(elf, dynamic), offsetof(elf, dynamic),
      sizeof foo.dynamic, SHN_DYNSTR, 0, sizeof(Elf64_Addr),
      sizeof(Elf64_Dyn) },
    /* .data */
    { 86, SHT_PROGBITS, SHF_WRITE | SHF_ALLOC,
      ADDR_RODATA + offsetof(elf, data), offsetof(elf, data), sizeof foo.data,
      SHN_UNDEF, 0, 4, 0 },
    /* .symtab */
    { 1, SHT_SYMTAB, 0, 0, offsetof(elf, symtab), sizeof foo.symtab,
      SHN_STRTAB, 32, sizeof(Elf64_Addr), sizeof(Elf64_Sym) },
    /* .strtab */
    { 9, SHT_STRTAB, 0, 0, offsetof(elf, strtab), sizeof foo.strtab,
      SHN_UNDEF, 0, 1, 0 },
    /* .shstrtab */
    { 17, SHT_STRTAB, 0, 0, offsetof(elf, shstrtab), sizeof foo.shstrtab,
      SHN_UNDEF, 0, 1, 0 }
  }
};
