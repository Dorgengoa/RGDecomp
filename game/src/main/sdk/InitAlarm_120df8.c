#include "types.h"

extern void RFU116_SetSyscall_5(void);
extern void KCopy_120da0(void);
extern void FlushCache(void);
extern void RFU091_3(void);

asm void InitAlarm_120df8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, (0x10001810 >> 16);
    sd         $31, 0x30($29);
    ori        $2, $2, (0x10001810 & 0xFFFF);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x100;
    bnez       $3, L00120EB8;
    ld        $31, 0x30($29);
    lui        $2, 0x44;
    addiu      $18, $0, 0x2;
    addiu      $16, $2, 0x7868;
    lw         $4, 0x7868($2);
    lw         $5, 0x4($16);
    jal        RFU116_SetSyscall_5;
    addiu     $17, $16, 0x10;
    lui        $5, 0x44;
    lui        $4, (0x80076000 >> 16);
    addiu      $5, $5, 0x7100;
    ori        $4, $4, (0x80076000 & 0xFFFF);
    jal        KCopy_120da0;
    addiu     $6, $0, 0x740;
    lui        $5, 0x44;
    lui        $4, (0x82000 >> 16);
    addiu      $5, $5, 0x7840;
    ori        $4, $4, (0x82000 & 0xFFFF);
    jal        KCopy_120da0;
    addiu     $6, $0, 0x28;
    jal        FlushCache;
    daddu     $4, $0, $0;
    jal        FlushCache;
    addiu     $4, $0, 0x2;
    lw         $4, 0x8($16);
    jal        RFU116_SetSyscall_5;
    lw        $5, 0xC($16);
    lw         $4, 0x0($17);
  L00120E90:
    jal        RFU091_3;
    addiu     $18, $18, 0x1;
    lw         $4, 0x0($17);
    daddu      $5, $2, $0;
    jal        RFU116_SetSyscall_5;
    addiu     $17, $17, 0x8;
    sltiu      $2, $18, 0x8;
    bnel       $2, $0, L00120E90;
    lw        $4, 0x0($17);
    ld         $31, 0x30($29);
  L00120EB8:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
