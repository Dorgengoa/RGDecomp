#include "types.h"

asm void IopResetCallbacksInvokeMaybe_1227e8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $19, 0x30($29);
    sd         $31, 0x40($29);
    daddu      $19, $5, $0;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    beqz       $4, L00122818;
    sd        $16, 0x0($29);
    lui        $2, 0x49;
    addiu      $3, $0, 0x20;
    b          L00122828;
    addiu     $2, $2, -0x2978;
  L00122818:
    lui        $2, 0x44;
    lui        $3, 0x44;
    lw         $2, 0x78C8($2);
    lw         $3, 0x78CC($3);
  L00122828:
    daddu      $18, $28, $0;
    blez       $3, L0012286C;
    daddu     $16, $2, $0;
    daddu      $17, $3, $0;
  L00122838:
    lw         $2, 0x0($16);
    beql       $2, $0, L00122864;
    addiu     $17, $17, -0x1;
    lw         $2, 0x8($16);
    daddu      $3, $28, $0;
    daddu      $28, $2, $0;
    lw         $6, 0x0($16);
    daddu      $4, $19, $0;
    jalr $31, $6;
    lw        $5, 0x4($16);
    addiu      $17, $17, -0x1;
  L00122864:
    bnez       $17, L00122838;
    addiu     $16, $16, 0x10;
  L0012286C:
    daddu      $2, $28, $0;
    daddu      $28, $18, $0;
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

