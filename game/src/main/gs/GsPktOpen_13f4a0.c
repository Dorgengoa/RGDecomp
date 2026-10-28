#include "types.h"

extern void GsEnvWritePacket_157190(void);

asm void GsPktOpen_13f4a0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $3, $0, 0x1;
    sd         $31, 0x10($29);
    sq         $16, 0x0($29);
    sw         $3, 0xE8($4);
    lw         $3, 0x0($4);
    beqz       $3, L0013F594;
    daddu     $16, $4, $0;
    sw         $0, 0xE8($16);
    lw         $2, 0x0($16);
    lw         $3, 0x2C($2);
    lw         $2, 0x28($2);
    sll        $3, $3, 4;
    addu       $2, $2, $3;
    sw         $2, 0xEC($16);
    sw         $2, 0xEC($16);
    lw         $2, 0xF0($16);
    bnel       $2, $0, L0013F500;
    lw        $8, 0xEC($16);
    lw         $2, 0xEC($16);
    dsll32     $2, $2, 4;
    dsrl32     $2, $2, 4;
    sw         $2, 0xF0($16);
    lw         $8, 0xEC($16);
  L0013F500:
    lui        $10, (0x10000009 >> 16);
    lui        $2, (0x50000009 >> 16);
    ori        $3, $10, (0x10000009 & 0xFFFF);
    ori        $4, $2, (0x50000009 & 0xFFFF);
    ori        $7, $0, 0x8002;
    sw         $8, 0xF4($16);
    addiu      $5, $0, 0xE;
    sw         $3, 0x0($8);
    addiu      $6, $0, 0x3F;
    sw         $0, 0x8($8);
    addiu      $3, $0, 0x1;
    sw         $0, 0x4($8);
    addiu      $2, $0, 0x1A;
    sw         $4, 0xC($8);
    lw         $9, 0xF4($16);
    addiu      $4, $16, 0x10;
    addiu      $8, $9, 0x10;
    sw         $8, 0xF4($16);
    sw         $8, 0x100($16);
    sw         $7, 0x10($9);
    sw         $10, 0x14($9);
    sw         $5, 0x18($9);
    sw         $0, 0x1C($9);
    lw         $7, 0xF4($16);
    addiu      $5, $7, 0x10;
    sw         $5, 0xF4($16);
    sd         $0, 0x10($7);
    addiu      $5, $5, 0x20;
    sd         $6, 0x18($7);
    sd         $3, 0x20($7);
    sd         $2, 0x28($7);
    jal        GsEnvWritePacket_157190;
    sw        $5, 0xF4($16);
    lw         $3, 0xF4($16);
    sll        $4, $2, 4;
    addu       $3, $3, $4;
    sw         $3, 0xF4($16);
  L0013F594:
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

