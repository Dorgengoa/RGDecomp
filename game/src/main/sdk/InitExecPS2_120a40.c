#include "types.h"

extern void PatchIsNeeded_1209d8(void);
extern void RFU116_SetSyscall_3(void);
extern void KCopy_120980(void);
extern void FlushCache(void);
extern void RFU091_2(void);

asm void InitExecPS2_120a40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $31, 0x30($29);
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    jal        PatchIsNeeded_1209d8;
    sd        $16, 0x0($29);
    beqz       $2, L00120AD4;
    lui       $2, 0x44;
    addiu      $18, $0, 0x2;
    addiu      $16, $2, 0x70E0;
    lw         $4, 0x70E0($2);
    lw         $5, 0x4($16);
    jal        RFU116_SetSyscall_3;
    addiu     $17, $16, 0x10;
    lui        $5, 0x44;
    lui        $4, (0x80074000 >> 16);
    addiu      $6, $0, 0x7A8;
    addiu      $5, $5, 0x6938;
    jal        KCopy_120980;
    ori       $4, $4, (0x80074000 & 0xFFFF);
    jal        FlushCache;
    daddu     $4, $0, $0;
    jal        FlushCache;
    addiu     $4, $0, 0x2;
    lw         $4, 0x8($16);
    jal        RFU116_SetSyscall_3;
    lw        $5, 0xC($16);
    lw         $4, 0x0($17);
  L00120AB0:
    jal        RFU091_2;
    addiu     $18, $18, 0x1;
    lw         $4, 0x0($17);
    daddu      $5, $2, $0;
    jal        RFU116_SetSyscall_3;
    addiu     $17, $17, 0x8;
    sltiu      $2, $18, 0x3;
    bnel       $2, $0, L00120AB0;
    lw        $4, 0x0($17);
  L00120AD4:
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
