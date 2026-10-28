#include "types.h"

extern void dpmul(void);
extern void dpadd(void);
extern void dpsub(void);
extern void dpdiv(void);
extern void DoubleCmp_13b948(void);

asm void IeeeSqrt_124130(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $20, 0x20($29);
    lui        $20, (0x80000000 >> 16);
    sd         $17, 0x8($29);
    sd         $18, 0x10($29);
    sd         $19, 0x18($29);
    sd         $21, 0x28($29);
    daddu      $2, $16, $0;
    dsll32     $7, $2, 0;
    dsra32     $7, $7, 0;
    dsra32     $5, $2, 0;
    lui        $3, (0x7FF00000 >> 16);
    and        $2, $5, $3;
    bne        $2, $3, L00124198;
    sd        $31, 0x30($29);
    daddu      $5, $16, $0;
    jal        dpmul;
    nop;
    daddu      $5, $16, $0;
    daddu      $4, $2, $0;
    jal        dpadd;
    nop;
    b          L0012442C;
    ld        $16, 0x0($29);
  L00124198:
    bgtz       $5, L001241E8;
    sra       $17, $5, 20;
    lui        $3, (0x7FFFFFFF >> 16);
    daddu      $2, $16, $0;
    ori        $3, $3, (0x7FFFFFFF & 0xFFFF);
    and        $3, $5, $3;
    or         $3, $3, $7;
    beql       $3, $0, L0012442C;
    ld        $16, 0x0($29);
    bgez       $5, L001241E8;
    nop;
    daddu      $5, $16, $0;
    jal        dpsub;
    nop;
    daddu      $4, $2, $0;
    daddu      $5, $2, $0;
    jal        dpdiv;
    nop;
    b          L0012442C;
    ld        $16, 0x0($29);
  L001241E8:
    bnez       $17, L00124260;
    lui       $2, (0xFFFFF >> 16);
    bnez       $5, L00124218;
    lui       $2, (0x100000 >> 16);
  L001241F8:
    srl        $2, $7, 11;
    sll        $7, $7, 21;
    or         $5, $5, $2;
    nop;
    nop;
    beqz       $5, L001241F8;
    addiu     $17, $17, -0x15;
    lui        $2, (0x100000 >> 16);
  L00124218:
    and        $2, $5, $2;
    bnez       $2, L00124244;
    daddu     $4, $0, $0;
    lui        $3, (0x100000 >> 16);
  L00124228:
    sll        $5, $5, 1;
    and        $2, $5, $3;
    nop;
    nop;
    nop;
    beqz       $2, L00124228;
    addiu     $4, $4, 0x1;
  L00124244:
    negu       $2, $4;
    subu       $3, $17, $4;
    srlv       $2, $7, $2;
    sllv       $7, $7, $4;
    addiu      $17, $3, 0x1;
    or         $5, $5, $2;
    lui        $2, (0xFFFFF >> 16);
  L00124260:
    addiu      $17, $17, -0x3FF;
    ori        $2, $2, (0xFFFFF & 0xFFFF);
    lui        $4, (0x100000 >> 16);
    and        $2, $5, $2;
    andi       $3, $17, 0x1;
    beqz       $3, L00124290;
    or        $5, $2, $4;
    and        $2, $7, $20;
    sll        $7, $7, 1;
    srl        $2, $2, 31;
    addu       $2, $5, $2;
    addu       $5, $5, $2;
  L00124290:
    and        $2, $7, $20;
    sll        $7, $7, 1;
    srl        $2, $2, 31;
    sra        $17, $17, 1;
    addu       $2, $5, $2;
    daddu      $12, $0, $0;
    addu       $5, $5, $2;
    daddu      $11, $0, $0;
    daddu      $18, $0, $0;
    daddu      $19, $0, $0;
    lui        $9, 0x20;
    nop;
  L001242C0:
    addu       $3, $11, $9;
    slt        $2, $5, $3;
    bnez       $2, L001242DC;
    and       $2, $7, $20;
    subu       $5, $5, $3;
    addu       $11, $3, $9;
    addu       $19, $19, $9;
  L001242DC:
    sll        $7, $7, 1;
    srl        $2, $2, 31;
    srl        $9, $9, 1;
    addu       $2, $5, $2;
    bnez       $9, L001242C0;
    addu      $5, $5, $2;
    lui        $9, (0x80000000 >> 16);
  L001242F8:
    daddu      $3, $11, $0;
    addu       $4, $12, $9;
    slt        $2, $3, $5;
    and        $10, $4, $20;
    bnez       $2, L00124320;
    sltu      $8, $7, $4;
    bne        $3, $5, L00124348;
    and       $2, $7, $20;
    bnel       $8, $0, L0012434C;
    sll       $7, $7, 1;
  L00124320:
    addu       $12, $4, $9;
    bne        $10, $20, L00124334;
    and       $6, $12, $20;
    addiu      $2, $11, 0x1;
    movz       $11, $2, $6;
  L00124334:
    subu       $5, $5, $3;
    subu       $7, $7, $4;
    addu       $18, $18, $9;
    subu       $5, $5, $8;
    and        $2, $7, $20;
  L00124348:
    sll        $7, $7, 1;
  L0012434C:
    srl        $2, $2, 31;
    srl        $9, $9, 1;
    addu       $2, $5, $2;
    bnez       $9, L001242F8;
    addu      $5, $5, $2;
    or         $2, $5, $7;
    beqz       $2, L001243D8;
    srl       $7, $18, 1;
    ori        $16, $0, 0xFFC0;
    dsll32     $16, $16, 14;
    daddu      $4, $16, $0;
    daddu      $5, $16, $0;
    jal        DoubleCmp_13b948;
    nop;
    bltz       $2, L001243D4;
    addiu     $2, $0, -0x1;
    bne        $18, $2, L001243A0;
    nop;
    daddu      $18, $0, $0;
    b          L001243D4;
    addiu     $19, $19, 0x1;
  L001243A0:
    daddu      $4, $16, $0;
    daddu      $5, $16, $0;
    jal        DoubleCmp_13b948;
    nop;
    blez       $2, L001243D0;
    andi      $2, $18, 0x1;
    addiu      $2, $0, -0x2;
    addiu      $3, $19, 0x1;
    xor        $2, $18, $2;
    addiu      $18, $18, 0x2;
    b          L001243D4;
    movz      $19, $3, $2;
  L001243D0:
    addu       $18, $18, $2;
  L001243D4:
    srl        $7, $18, 1;
  L001243D8:
    sra        $2, $19, 1;
    lui        $5, (0x3FE00000 >> 16);
    addu       $5, $5, $2;
    or         $2, $7, $20;
    andi       $4, $19, 0x1;
    sll        $3, $17, 20;
    movn       $7, $2, $4;
    addu       $5, $5, $3;
    dsll32     $4, $5, 0;
    lui        $2, (0xFFFF0000 >> 16);
    dsrl32     $2, $2, 0;
    and        $21, $21, $2;
    addiu      $2, $0, -0x1;
    dsll32     $2, $2, 0;
    dsll32     $3, $7, 0;
    or         $21, $21, $4;
    dsrl32     $3, $3, 0;
    and        $21, $21, $2;
    or         $16, $21, $3;
    daddu      $2, $16, $0;
    ld         $16, 0x0($29);
  L0012442C:
    ld         $17, 0x8($29);
    ld         $18, 0x10($29);
    ld         $19, 0x18($29);
    ld         $20, 0x20($29);
    ld         $21, 0x28($29);
    ld         $31, 0x30($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
