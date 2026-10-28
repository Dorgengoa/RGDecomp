#include "types.h"

extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void MpegKickSprDmaMaybe_10e148(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $16, 0x0($29);
    sd         $31, 0x30($29);
    daddu      $16, $4, $0;
    sd         $18, 0x20($29);
    sd         $17, 0x10($29);
    lw         $2, 0x87C($16);
    bnez       $2, L0010E2B0;
    ld        $31, 0x30($29);
    lw         $24, 0x820($16);
    addiu      $4, $0, 0x140;
    lui        $18, 0x48;
    lui        $2, (0xFFFFFFF >> 16);
    mult       $3, $24, $4;
    ori        $2, $2, (0xFFFFFFF & 0xFFFF);
    lui        $5, (0x20000010 >> 16);
    daddu      $10, $0, $0;
    addu       $4, $3, $16;
    addiu      $3, $18, 0x59C0;
    lw         $12, 0x6CC($4);
    and        $3, $3, $2;
    blez       $12, L0010E238;
    or        $11, $3, $5;
    addiu      $15, $16, 0x5A8;
    addiu      $14, $16, 0x5B8;
    addiu      $13, $12, -0x1;
    addiu      $17, $16, 0x5A0;
    nop;
  L0010E1B8:
    addiu      $4, $0, 0x140;
    sll        $2, $10, 2;
    mult       $4, $24, $4;
    xor        $3, $10, $13;
    addiu      $5, $0, 0x3;
    lui        $6, (0xFFFFFFF >> 16);
    movz       $5, $0, $3;
    ori        $6, $6, (0xFFFFFFF & 0xFFFF);
    lui        $9, (0x30000000 >> 16);
    dsll       $5, $5, 28;
    addu       $2, $2, $4;
    addiu      $7, $0, 0x30;
    addu       $4, $14, $2;
    addiu      $10, $10, 0x1;
    addu       $2, $15, $2;
    slt        $8, $10, $12;
    lw         $3, 0x0($2);
    lw         $2, 0x0($4);
    and        $3, $3, $6;
    and        $2, $2, $6;
    dsll32     $3, $3, 0;
    dsll32     $2, $2, 0;
    or         $3, $3, $9;
    or         $2, $2, $5;
    or         $3, $3, $7;
    or         $2, $2, $7;
    sd         $3, (0x20000000 & 0xFFFF)($11);
    sd         $2, (0x20000010 & 0xFFFF)($11);
    bnez       $8, L0010E1B8;
    addiu     $11, $11, (0x20000020 & 0xFFFF);
    b          L0010E23C;
    nop;
  L0010E238:
    addiu      $17, $16, 0x5A0;
  L0010E23C:
    jal        DisableIntr_120660;
    nop;
    sync;
    lw         $6, 0x820($16);
    addiu      $3, $0, 0x140;
    lui        $7, (0x1000D480 >> 16);
    lui        $8, (0x1000D430 >> 16);
    mult       $4, $6, $3;
    ori        $7, $7, (0x1000D480 & 0xFFFF);
    addiu      $10, $18, 0x59C0;
    ori        $8, $8, (0x1000D430 & 0xFFFF);
    lui        $3, (0x1000D420 >> 16);
    addiu      $9, $0, 0x105;
    ori        $3, $3, (0x1000D420 & 0xFFFF);
    addu       $6, $4, $17;
    lw         $5, 0x0($6);
    lui        $4, (0x1000D400 >> 16);
    ori        $4, $4, (0x1000D400 & 0xFFFF);
    sw         $5, 0x0($7);
    sw         $10, 0x0($8);
    sw         $0, 0x0($3);
    sw         $9, 0x0($4);
    beqz       $2, L0010E2B0;
    ld        $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    j          EnableIntr_1206b0;
    addiu     $29, $29, 0x40;
  L0010E2B0:
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}

