#include "types.h"

extern void memclr(void);
extern void sceDmaPutEnv(void);

asm void sceDmaReset(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    lui        $2, (0x1000E000 >> 16);
    sd         $17, 0x30($29);
    ori        $2, $2, (0x1000E000 & 0xFFFF);
    sd         $16, 0x20($29);
    lui        $6, 0x45;
    sd         $31, 0x40($29);
    lui        $3, 0x44;
    daddu      $16, $4, $0;
    addiu      $3, $3, 0x5F20;
    lw         $5, 0x0($2);
    addiu      $6, $6, 0x6028;
    addiu      $4, $0, 0x9;
    andi       $17, $5, 0x1;
  L00109D70:
    lw         $2, 0x0($6);
    beql       $2, $0, L00109D9C;
    addiu     $3, $3, 0x4;
    lw         $2, 0x0($3);
    sw         $0, 0x80($2);
    sw         $0, 0x0($2);
    sw         $0, 0x30($2);
    sw         $0, 0x10($2);
    sw         $0, 0x50($2);
    sw         $0, 0x40($2);
    addiu      $3, $3, 0x4;
  L00109D9C:
    addiu      $4, $4, -0x1;
    bgez       $4, L00109D70;
    addiu     $6, $6, 0x4;
    lui        $3, (0x1000E010 >> 16);
    ori        $2, $0, 0xFF1F;
    ori        $3, $3, (0x1000E010 & 0xFFFF);
    lui        $6, (0xFF1F0000 >> 16);
    sw         $2, 0x0($3);
    daddu      $4, $29, $0;
    addiu      $5, $0, 0x14;
    lw         $2, 0x0($3);
    and        $2, $2, $6;
    jal        memclr;
    sw        $2, 0x0($3);
    jal        sceDmaPutEnv;
    daddu     $4, $29, $0;
    addiu      $3, $0, 0x1;
    bne        $16, $3, L00109E00;
    daddu     $2, $17, $0;
    lui        $3, (0x1000E000 >> 16);
    ori        $3, $3, (0x1000E000 & 0xFFFF);
    lw         $2, 0x0($3);
    ori        $2, $2, 0x1;
    sw         $2, 0x0($3);
    daddu      $2, $17, $0;
  L00109E00:
    ld         $31, 0x40($29);
    ld         $17, 0x30($29);
    ld         $16, 0x20($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

