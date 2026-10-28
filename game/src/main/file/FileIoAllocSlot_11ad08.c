#include "types.h"

extern void StdioInitSemas_11ac18(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void FileIoAllocSlot_11ad08(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        StdioInitSemas_11ac18;
    lui       $17, 0x44;
    jal        WaitSema;
    lw        $4, 0x62A8($17);
    lui        $3, 0x49;
    addiu      $16, $3, -0x6740;
    addiu      $3, $16, 0x200;
    sltu       $2, $16, $3;
    beqz       $2, L0011AD70;
    lui       $5, (0x10000000 >> 16);
    lw         $2, 0x4($16);
    nop;
  L0011AD48:
    bnel       $2, $0, L0011AD64;
    addiu     $16, $16, 0x10;
    lw         $4, 0x62A8($17);
    jal        SignalSema;
    sw        $5, 0x4($16);
    b          L0011AD7C;
    daddu     $2, $16, $0;
  L0011AD64:
    sltu       $2, $16, $3;
    bnel       $2, $0, L0011AD48;
    lw        $2, 0x4($16);
  L0011AD70:
    jal        SignalSema;
    lw        $4, 0x62A8($17);
    daddu      $2, $0, $0;
  L0011AD7C:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
