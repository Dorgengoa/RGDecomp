#include "types.h"

extern void Terminate_100ce0(void);
extern void EhSkipActions_102070(void);
extern void DecodeVarInt_100f70(void);

asm void EhGetCatchRecord_101700(void)
{
    .set noreorder;
    addiu      $29, $29, -0x310;
    addiu      $6, $0, 0x15;
    sd         $31, 0x10($29);
    addiu      $7, $29, 0x60;
    sq         $16, 0x0($29);
    lw         $2, 0x0($5);
    daddu      $16, $4, $0;
    addiu      $8, $16, 0x20;
    sw         $2, 0x20($29);
    lw         $2, 0x4($5);
    sw         $2, 0x24($29);
    lw         $2, 0x8($5);
    sw         $2, 0x28($29);
    lw         $2, 0xC($5);
    sw         $2, 0x2C($29);
    lw         $2, 0x10($5);
    sw         $2, 0x30($29);
    lwc1       $f0, 0x14($5);
    swc1       $f0, 0x34($29);
    lw         $2, 0x0($4);
    sw         $2, 0x40($29);
    lw         $2, 0x4($4);
    sw         $2, 0x44($29);
    lw         $2, 0x8($4);
    sw         $2, 0x48($29);
    lw         $2, 0xC($4);
    sw         $2, 0x4C($29);
    lw         $2, 0x10($4);
    sw         $2, 0x50($29);
    lw         $2, 0x14($4);
    sw         $2, 0x54($29);
    lw         $2, 0x18($4);
    sw         $2, 0x58($29);
    lw         $2, 0x1C($4);
    sw         $2, 0x5C($29);
  L0010178C:
    lq         $3, 0x0($8);
    addiu      $6, $6, -0x1;
    lq         $2, 0x10($8);
    sq         $3, 0x0($7);
    addiu      $8, $8, 0x20;
    sq         $2, 0x10($7);
    bgtz       $6, L0010178C;
    addiu     $7, $7, 0x20;
    lw         $2, 0x28($29);
    beql       $2, $0, L001017C0;
    daddu     $2, $0, $0;
    lbu        $2, 0x0($2);
    andi       $2, $2, 0x1F;
  L001017C0:
    andi       $2, $2, 0xFF;
  L001017C4:
    andi       $2, $2, 0xFF;
    sltiu      $1, $2, 0x10;
    beqz       $1, L001017F0;
    nop;
    lui        $3, 0x45;
    sll        $2, $2, 2;
    addiu      $3, $3, 0x55A0;
    addu       $2, $2, $3;
    lw         $2, 0x0($2);
    jr         $2;
    nop;
  L001017F0:
    jal        Terminate_100ce0;
    nop;
    b          L00101810;
    nop;
    jal        EhSkipActions_102070;
    addiu     $4, $29, 0x20;
    b          L001017C4;
    andi      $2, $2, 0xFF;
  L00101810:
    lw         $2, 0x28($29);
    addiu      $5, $29, 0x30C;
    jal        DecodeVarInt_100f70;
    addiu     $4, $2, 0x1;
    lw         $3, 0x58($29);
    lw         $2, 0x30C($29);
    addu       $2, $3, $2;
    lw         $3, 0x4($2);
    sw         $3, 0x0($16);
    lw         $3, 0x0($2);
    sw         $3, 0x4($16);
    sw         $0, 0x8($16);
    sw         $2, 0xC($16);
    ld         $31, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x310;
}

