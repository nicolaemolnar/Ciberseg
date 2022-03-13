# Criptography problem: Nope

## Description
*Chuck Testa loves stego!*

## Explicit hints
- None

## Implicit hints
- *La clave no es flag{ASM} }: )*

## Enumeration
Information obtained by enumeration of the provided file and web search.

- **Type of file**: ELF 64-bit LSB executable, not stripped
    - ![File command](../images/file.png)
- **Executable**: Yes
    - Params: Apparently none.
    - Output: *La clave no es flag{ASM} }: )*
    - ![File execution](../images/execution.png)
- **Content**:
    - Raw contents: ![Raw content](../images/cat.png) 
    - *Strings* output: ![Strings output](../images/strings.png)
        - Relevant Data:  
          - Hint 1: *La clave no es flag{ASM} }: )*
          - Hint 2: *the_flag*
- **Web Search**:
    - *Chuck Testa loves stego!*: Nothing relevant
- **Exiftool**:
    - ![Exiftool output](../images/exiftool.png)
    -  *File Type*: ELF 64-bit LSB executable
    -  *MIME Type*: application/octet-stream
    -  *Permissions*: rwx rwx rwx
- **GDB**: *Code snooping with gdb*.
    - Disassembled main: ![GDB disassembled main](../images/gdb_dis_main.png)
    - Breakpoint at main: ![GDB breakpoint main](../images/gdb_b_main.png)
    - Reading value of flagX: Using the information gathered from the *strings* output, we look at the content of flag{1,2,...,25}
        - ![GDB read flagX](../images/gdb_read_flagX.png)
        - We suppose there is a string "La flag no es flag{ASM} }: )" in the address of flag: 
        - ![picture 5](../images/gdb_read_flag.png)  
  