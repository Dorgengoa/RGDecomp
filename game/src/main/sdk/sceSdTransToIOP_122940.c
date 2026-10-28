#include "types.h"

extern void sceSifSetDma(void);
extern void sceSifDmaStat(void);

asm void sceSdTransToIOP_122940(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    daddu      $8, $5, $0;
    sd         $17, 0x10($29);
    sd         $31, 0x20($29);
    daddu      $17, $7, $0;
    beqz       $17, L0012298C;
    sd        $16, 0x0($29);
    lui        $3, 0x49;
    addiu      $5, $0, 0x1;
    addiu      $2, $3, -0x2740;
    sw         $4, -0x2740($3);
    sw         $8, 0x4($2);
    daddu      $4, $2, $0;
    sw         $6, 0x8($2);
    jal        sceSifSetDma;
    sw        $0, 0xC($2);
    daddu      $16, $2, $0;
    bnez       $16, L00122994;
    addiu     $2, $0, 0x1;
  L0012298C:
    b          L001229B0;
    addiu     $2, $0, -0x1;
  L00122994:
    bne        $17, $2, L001229B0;
    daddu     $2, $0, $0;
    nop;
  L001229A0:
    jal        sceSifDmaStat;
    daddu     $4, $16, $0;
    bgez       $2, L001229A0;
    daddu     $2, $0, $0;
  L001229B0:
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x30;
}
