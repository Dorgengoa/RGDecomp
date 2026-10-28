#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void IopResetCallbackRegisterMaybe_1226d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    daddu      $19, $6, $0;
    sd         $16, 0x0($29);
    daddu      $18, $5, $0;
    sd         $31, 0x40($29);
    daddu      $16, $4, $0;
    bgez       $16, L0012271C;
    sd        $17, 0x10($29);
    lui        $2, (0x7FFFFFFF >> 16);
    lui        $3, 0x49;
    ori        $2, $2, (0x7FFFFFFF & 0xFFFF);
    addiu      $17, $3, -0x2978;
    and        $16, $16, $2;
    b          L0012272C;
    addiu     $2, $0, 0x20;
  L0012271C:
    lui        $2, 0x44;
    lui        $3, 0x44;
    lw         $17, 0x78C8($2);
    lw         $2, 0x78CC($3);
  L0012272C:
    sltu       $2, $16, $2;
    bnez       $2, L00122744;
    nop;
    lui        $2, (0x80000069 >> 16);
    b          L00122774;
    ori       $2, $2, (0x80000069 & 0xFFFF);
  L00122744:
    jal        DisableIntr_120660;
    nop;
    sll        $3, $16, 4;
    addu       $3, $3, $17;
    sw         $18, 0x0($3);
    sw         $19, 0x4($3);
    daddu      $4, $28, $0;
    beqz       $2, L00122770;
    sw        $4, 0x8($3);
    jal        EnableIntr_1206b0;
    nop;
  L00122770:
    daddu      $2, $0, $0;
  L00122774:
    ld         $31, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}
