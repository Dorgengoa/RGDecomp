#include "types.h"

extern void RFU116_SetSyscall(void);
extern void KCopy_11fec8(void);
extern void FlushCache(void);
extern void RFU091(void);

asm void InitTLBFunctions_11ff30(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $2, 0x44;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    addiu      $18, $0, 0x3;
    sd         $16, 0x0($29);
    sd         $31, 0x30($29);
    addiu      $16, $2, 0x6648;
    lw         $4, 0x6648($2);
    addiu      $17, $16, 0x18;
    jal        RFU116_SetSyscall;
    lw        $5, 0x4($16);
    lui        $5, 0x44;
    lui        $4, (0x80075000 >> 16);
    addiu      $6, $0, 0x330;
    addiu      $5, $5, 0x62C8;
    jal        KCopy_11fec8;
    ori       $4, $4, (0x80075000 & 0xFFFF);
    jal        FlushCache;
    daddu     $4, $0, $0;
    jal        FlushCache;
    addiu     $4, $0, 0x2;
    lw         $4, 0x8($16);
    jal        RFU116_SetSyscall;
    lw        $5, 0xC($16);
    lw         $4, 0x10($16);
    jal        RFU116_SetSyscall;
    lw        $5, 0x14($16);
    lw         $4, 0x0($17);
    nop;
  L0011FFA8:
    jal        RFU091;
    addiu     $18, $18, 0x1;
    lw         $4, 0x0($17);
    daddu      $5, $2, $0;
    jal        RFU116_SetSyscall;
    addiu     $17, $17, 0x8;
    sltiu      $2, $18, 0x8;
    bnel       $2, $0, L0011FFA8;
    lw        $4, 0x0($17);
    jal        RFU091;
    addiu     $4, $0, 0x3;
    lui        $3, 0x44;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    sw         $2, 0x6640($3);
    jr         $31;
    addiu     $29, $29, 0x40;
}
