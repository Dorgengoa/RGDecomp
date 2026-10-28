#include "types.h"

extern void RFU116_SetSyscall_4(void);
extern void KCopy_120af0(void);
extern void strlen(void);

asm void KernelSetArgvMaybe_120b40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    lui        $2, 0x44;
    sd         $19, 0x40($29);
    lui        $3, 0x44;
    lw         $19, 0x6640($2);
    addiu      $7, $3, 0x70F8;
    sd         $21, 0x60($29);
    sd         $20, 0x50($29);
    addiu      $2, $19, 0x40;
    sd         $18, 0x30($29);
    daddu      $21, $2, $0;
    sd         $17, 0x20($29);
    daddu      $18, $5, $0;
    sd         $16, 0x10($29);
    daddu      $20, $6, $0;
    sd         $31, 0x70($29);
    daddu      $16, $4, $0;
    lw         $4, 0x70F8($3);
    lw         $5, 0x4($7);
    jal        RFU116_SetSyscall_4;
    sw        $2, 0x0($29);
    slti       $3, $18, 0x10;
    addiu      $2, $0, 0xF;
    daddu      $4, $19, $0;
    movz       $18, $2, $3;
    daddu      $5, $29, $0;
    jal        KCopy_120af0;
    addiu     $6, $0, 0x4;
    addiu      $19, $19, 0x4;
    jal        strlen;
    daddu     $4, $16, $0;
    addiu      $17, $2, 0x1;
    lw         $4, 0x0($29);
    daddu      $5, $16, $0;
    jal        KCopy_120af0;
    daddu     $6, $17, $0;
    lw         $3, 0x0($29);
    addu       $3, $3, $17;
    blez       $18, L00120C30;
    sw        $3, 0x0($29);
    daddu      $16, $20, $0;
    nop;
  L00120BE8:
    daddu      $4, $19, $0;
    daddu      $5, $29, $0;
    addiu      $6, $0, 0x4;
    jal        KCopy_120af0;
    addiu     $19, $19, 0x4;
    addiu      $18, $18, -0x1;
    jal        strlen;
    lw        $4, 0x0($16);
    addiu      $17, $2, 0x1;
    lw         $5, 0x0($16);
    lw         $4, 0x0($29);
    daddu      $6, $17, $0;
    jal        KCopy_120af0;
    addiu     $16, $16, 0x4;
    lw         $3, 0x0($29);
    addu       $3, $3, $17;
    bnez       $18, L00120BE8;
    sw        $3, 0x0($29);
  L00120C30:
    daddu      $2, $21, $0;
    ld         $31, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}
