#include "types.h"

extern void sceGsGetGParam_1082a0(void);

asm void sceGszbufaddr(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sll        $6, $6, 16;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sll        $17, $4, 16;
    sd         $18, 0x20($29);
    sll        $16, $5, 16;
    sra        $16, $16, 16;
    sra        $17, $17, 16;
    sd         $31, 0x30($29);
    jal        sceGsGetGParam_1082a0;
    sra       $18, $6, 16;
    addiu      $3, $16, 0x3F;
    daddu      $5, $2, $0;
    addiu      $4, $0, -0x1;
    addiu      $16, $16, 0x7E;
    slt        $2, $4, $3;
    andi       $17, $17, 0x2;
    movn       $16, $3, $2;
    beqz       $17, L0010886C;
    sra       $16, $16, 6;
    addiu      $2, $18, 0x3F;
    addiu      $3, $18, 0x7E;
    slt        $4, $4, $2;
    movn       $3, $2, $4;
    b          L00108880;
    sra       $6, $3, 6;
  L0010886C:
    addiu      $2, $18, 0x1F;
    addiu      $3, $18, 0x3E;
    slt        $4, $4, $2;
    movn       $3, $2, $4;
    sra        $6, $3, 5;
  L00108880:
    ld         $2, 0x0($5);
    ori        $3, $0, 0xFFFF;
    dsll32     $3, $3, 0;
    ori        $3, $3, 0xFFFF;
    addiu      $4, $0, 0x1;
    and        $2, $2, $3;
    bne        $2, $4, L001088A8;
    mult      $2, $16, $6;
    b          L001088AC;
    sll       $2, $2, 16;
  L001088A8:
    sll        $2, $2, 17;
  L001088AC:
    sra        $2, $2, 16;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

