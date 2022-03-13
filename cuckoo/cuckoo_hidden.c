#include <stddef.h>
#include <elf.h>

#define ADDR_TEXT 0x00400000

enum sections
{
  SHN_TEXT = 1, SHN_DATA, SHN_SYMTAB, SHN_STRTAB, SHN_SHSTRTAB, SHN_COUNT
};

typedef struct elf
{
  Elf64_Ehdr      ehdr;
  Elf64_Phdr      phdrs[3];
  unsigned char   pad1[3864];
  unsigned char   text[256];
  unsigned char   pad2[3840];
  unsigned char   data[81];
  unsigned char   pad3[7];
  Elf64_Sym       symtab[18];
  char            strtab[110];
  char            shstrtab[39];
  unsigned char   pad4[3];
  Elf64_Shdr      shdrs[SHN_COUNT];
} elf;

elf foo =
{
  /* ehdr */
  {
    { 0x7F, 'E', 'L', 'F', ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_SYSV,
      0, 0, 0, 0, 0, 0, 0, 0 },
    ET_EXEC, EM_X86_64, EV_CURRENT, ADDR_TEXT + offsetof(elf, text) + 14,
    offsetof(elf, phdrs), offsetof(elf, shdrs), 0, sizeof(Elf64_Ehdr),
    sizeof(Elf64_Phdr), sizeof foo.phdrs / sizeof *foo.phdrs,
    sizeof(Elf64_Shdr), sizeof foo.shdrs / sizeof *foo.shdrs, SHN_SHSTRTAB
  },
  /* phdrs */
  {
    { PT_LOAD, PF_R, 0, ADDR_TEXT, ADDR_TEXT, offsetof(elf, pad1),
      offsetof(elf, pad1), 0x1000 },
    { PT_LOAD, PF_R | PF_X, offsetof(elf, text),
      ADDR_TEXT + offsetof(elf, text), ADDR_TEXT + offsetof(elf, text),
      sizeof foo.text, sizeof foo.text, 0x1000 },
    { PT_LOAD, PF_R | PF_W, offsetof(elf, data),
      ADDR_TEXT + offsetof(elf, data), ADDR_TEXT + offsetof(elf, data),
      sizeof foo.data, sizeof foo.data, 0x1000 }
  },
  /* pad1 */
  { 0 },
  /* text */
  {
    0x48, 0x8D, 0x34, 0x25, 0x00, 0x20, 0x40, 0x00, 0xE8, 0xBE, 0x00, 0x00,
    0x00, 0xC3, 0xE8, 0x05, 0x00, 0x00, 0x00, 0xE9, 0xDC, 0x00, 0x00, 0x00,
    0x55, 0x68, 0xFE, 0xCA, 0x00, 0x00, 0x48, 0x89, 0xE5, 0x48, 0x81, 0xEC,
    0x02, 0x01, 0x00, 0x00, 0x66, 0xC7, 0x85, 0xFE, 0xFE, 0xFF, 0xFF, 0x00,
    0x00, 0xB8, 0x00, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x48,
    0x31, 0xD2, 0x66, 0x8B, 0x95, 0xFE, 0xFE, 0xFF, 0xFF, 0x48, 0x8D, 0xB4,
    0x15, 0x00, 0xFF, 0xFF, 0xFF, 0x48, 0x31, 0xD2, 0xBA, 0x01, 0x00, 0x00,
    0x00, 0x0F, 0x05, 0x8A, 0x16, 0x66, 0x31, 0xC9, 0x66, 0x8B, 0x8D, 0xFE,
    0xFE, 0xFF, 0xFF, 0x66, 0xFF, 0xC1, 0x66, 0x89, 0x8D, 0xFE, 0xFE, 0xFF,
    0xFF, 0x80, 0xFA, 0x0A, 0x75, 0xBF, 0x66, 0x31, 0xD2, 0x66, 0x8B, 0x95,
    0xFE, 0xFE, 0xFF, 0xFF, 0xC6, 0x84, 0x15, 0xFD, 0xFE, 0xFF, 0xFF, 0x00,
    0x48, 0x81, 0xC4, 0x02, 0x01, 0x00, 0x00, 0x5A, 0x81, 0xFA, 0xFE, 0xCA,
    0x00, 0x00, 0x74, 0x0F, 0x48, 0x8D, 0x34, 0x25, 0x3E, 0x20, 0x40, 0x00,
    0xE8, 0x2A, 0x00, 0x00, 0x00, 0xEB, 0x0D, 0x48, 0x8D, 0x34, 0x25, 0x20,
    0x20, 0x40, 0x00, 0xE8, 0x1B, 0x00, 0x00, 0x00, 0x5D, 0xC3, 0x55, 0x48,
    0x89, 0xE5, 0x48, 0x31, 0xD2, 0x48, 0xFF, 0xC2, 0xB3, 0x00, 0x3A, 0x1C,
    0x16, 0x75, 0xF6, 0x48, 0x31, 0xC0, 0x48, 0x8D, 0x02, 0x5D, 0xC3, 0x55,
    0x48, 0x89, 0xE5, 0x48, 0x83, 0xEC, 0x10, 0xE8, 0xDA, 0xFF, 0xFF, 0xFF,
    0x48, 0x89, 0x45, 0xF0, 0xB8, 0x04, 0x00, 0x00, 0x00, 0xBB, 0x01, 0x00,
    0x00, 0x00, 0x48, 0x89, 0xF1, 0x8B, 0x55, 0xF0, 0xCD, 0x80, 0x48, 0x83,
    0xC4, 0x10, 0x5D, 0xC3, 0xB8, 0x01, 0x00, 0x00, 0x00, 0xBB, 0x00, 0x00,
    0x00, 0x00, 0xCD, 0x80
  },
  /* pad2 */
  { 0 },
  /* data */
  "La flag es flag{*************}\n\0Gracias por portarte bien :)\n\0Muy mal"
    " hecho :'(\n",
  /* pad3 */
  { 0 },
  /* symtab */
  {
    { 0, 0, 0, SHN_UNDEF, 0, 0 },
    /* the.asm */
    { 1, ELF64_ST_INFO(STB_LOCAL, STT_FILE), STV_DEFAULT, SHN_ABS, 0, 0 },
    /* flag */
    { 27, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_TEXT + offsetof(elf, data), 0 },
    /* gracias */
    { 9, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_TEXT + offsetof(elf, data) + 0x20, 0 },
    /* mal */
    { 17, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_TEXT + offsetof(elf, data) + 0x3E, 0 },
    /* print_flag */
    { 21, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text), 0 },
    /* read_line */
    { 32, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0x18, 0 },
    /* read_loop */
    { 42, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0x31, 0 },
    /* not_bad */
    { 52, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xA3, 0 },
    /* sigue */
    { 60, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xB0, 0 },
    /* len */
    { 66, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xB2, 0 },
    /* len_start */
    { 70, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xB9, 0 },
    /* print */
    { 80, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xCB, 0 },
    /* end */
    { 106, ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 0xF4, 0 },
    /* _start */
    { 73, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_TEXT,
      ADDR_TEXT + offsetof(elf, text) + 14, 0 },
    /* __bss_start */
    { 86, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_TEXT + offsetof(elf, pad3), 0 },
    /* _edata */
    { 98, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      ADDR_TEXT + offsetof(elf, pad3), 0 },
    /* _end */
    { 105, ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE), STV_DEFAULT, SHN_DATA,
      0x402058, 0 }
  },
  /* strtab */
  "\0the.asm\0gracias\0mal\0print_flag\0read_line\0read_loop\0not_bad\0sigue"
    "\0len\0len_start\0print\0__bss_start\0_edata\0_end",
  /* shstrtab */
  "\0.symtab\0.strtab\0.shstrtab\0.text\0.data",
  /* pad4 */
  { 0 },
  /* shdrs */
  {
    { 0, SHT_NULL, 0, 0, 0, 0, SHN_UNDEF, 0, 0, 0 },
    /* .text */
    { 27, SHT_PROGBITS, SHF_EXECINSTR | SHF_ALLOC,
      ADDR_TEXT + offsetof(elf, text), offsetof(elf, text), sizeof foo.text,
      SHN_UNDEF, 0, 0x10, 0 },
    /* .data */
    { 33, SHT_PROGBITS, SHF_WRITE | SHF_ALLOC,
      ADDR_TEXT + offsetof(elf, data), offsetof(elf, data), sizeof foo.data,
      SHN_UNDEF, 0, 4, 0 },
    /* .symtab */
    { 1, SHT_SYMTAB, 0, 0, offsetof(elf, symtab), sizeof foo.symtab,
      SHN_STRTAB, 14, sizeof(Elf64_Addr), sizeof(Elf64_Sym) },
    /* .strtab */
    { 9, SHT_STRTAB, 0, 0, offsetof(elf, strtab), sizeof foo.strtab,
      SHN_UNDEF, 0, 1, 0 },
    /* .shstrtab */
    { 17, SHT_STRTAB, 0, 0, offsetof(elf, shstrtab), sizeof foo.shstrtab,
      SHN_UNDEF, 0, 1, 0 }
  }
};
