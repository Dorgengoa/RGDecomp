#include "types.h"

extern void StdioInitSemas_11ac18(void);
extern void WaitSema(void);
extern void SignalSema(void);

asm void FileIoGetSlot_11ae80(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $16, 0x0($29);
    sd         $17, 0x10($29);
    daddu      $16, $4, $0;
    sd         $31, 0x20($29);
    jal        StdioInitSemas_11ac18;
    lui       $17, 0x44;
    jal        WaitSema;
    lw        $4, 0x62A8($17);
    sltiu      $3, $16, 0x20;
    bnez       $3, L0011AEC0;
    lui       $2, 0x49;
    jal        SignalSema;
    lw        $4, 0x62A8($17);
    b          L0011AED8;
    daddu     $2, $0, $0;
  L0011AEC0:
    sll        $16, $16, 4;
    addiu      $2, $2, -0x6740;
    lw         $4, 0x62A8($17);
    jal        SignalSema;
    addu      $16, $16, $2;
    daddu      $2, $16, $0;
  L0011AED8:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
