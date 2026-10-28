#include "types.h"

extern void Balloc_131cf0(void);
extern void memcpy(void);
extern void _Bfree(void);

asm void Multadd_131dc8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    daddu      $8, $6, $0;
    sd         $17, 0x8($29);
    daddu      $17, $5, $0;
    sd         $19, 0x18($29);
    daddu      $19, $7, $0;
    sd         $20, 0x20($29);
    daddu      $20, $4, $0;
    sd         $16, 0x0($29);
    addiu      $7, $17, 0x14;
    sd         $18, 0x10($29);
    daddu      $9, $0, $0;
    sd         $31, 0x28($29);
    lw         $18, 0x10($17);
  L00131E00:
    lw         $3, 0x0($7);
    addiu      $9, $9, 0x1;
    slt        $6, $9, $18;
    andi       $4, $3, 0xFFFF;
    srl        $3, $3, 16;
    mult       $2, $4, $8;
    mult       $3, $3, $8;
    addu       $4, $2, $19;
    srl        $5, $4, 16;
    andi       $4, $4, 0xFFFF;
    addu       $3, $3, $5;
    sll        $2, $3, 16;
    srl        $19, $3, 16;
    addu       $2, $2, $4;
    sw         $2, 0x0($7);
    bnez       $6, L00131E00;
    addiu     $7, $7, 0x4;
    beqz       $19, L00131EB0;
    daddu     $2, $17, $0;
    lw         $2, 0x8($17);
    slt        $2, $18, $2;
    bnez       $2, L00131E9C;
    sll       $2, $18, 2;
    lw         $5, 0x4($17);
    daddu      $4, $20, $0;
    jal        Balloc_131cf0;
    addiu     $5, $5, 0x1;
    lw         $6, 0x10($17);
    daddu      $16, $2, $0;
    addiu      $5, $17, 0xC;
    sll        $6, $6, 2;
    addiu      $4, $16, 0xC;
    jal        memcpy;
    addiu     $6, $6, 0x8;
    daddu      $4, $20, $0;
    daddu      $5, $17, $0;
    jal        _Bfree;
    daddu     $17, $16, $0;
    sll        $2, $18, 2;
  L00131E9C:
    addiu      $18, $18, 0x1;
    addu       $2, $2, $17;
    sw         $19, 0x14($2);
    sw         $18, 0x10($17);
    daddu      $2, $17, $0;
  L00131EB0:
    ld         $16, 0x0($29);
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $31, 0x28($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
