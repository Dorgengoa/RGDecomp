#include "types.h"

extern void StdioInitSemas_11ac18(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void FileIoCountSlots_11ac88(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    lui        $17, 0x44;
    sd         $31, 0x20($29);
    jal        StdioInitSemas_11ac18;
    daddu     $16, $0, $0;
    jal        WaitSema;
    lw        $4, 0x62A8($17);
    lui        $3, 0x49;
    addiu      $5, $3, -0x6740;
    addiu      $3, $5, 0x200;
    sltu       $2, $5, $3;
    beqz       $2, L0011ACE4;
    daddu     $6, $3, $0;
    nop;
  L0011ACC8:
    lw         $4, 0x4($5);
    addiu      $3, $16, 0x1;
    addiu      $5, $5, 0x10;
    movn       $16, $3, $4;
    sltu       $2, $5, $6;
    bnez       $2, L0011ACC8;
    nop;
  L0011ACE4:
    jal        SignalSema;
    lw        $4, 0x62A8($17);
    daddu      $2, $16, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
