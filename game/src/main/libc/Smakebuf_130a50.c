#include "types.h"

extern void FstatR_130310(void);
extern void MallocR_1310d0(void);
extern void IsattyStub_116d50(void);

asm void Smakebuf_130a50(void)
{
    .set noreorder;
    addiu      $29, $29, -0x90;
    sd         $16, 0x70($29);
    daddu      $16, $4, $0;
    sd         $17, 0x78($29);
    sd         $18, 0x80($29);
    sd         $31, 0x88($29);
    lhu        $3, 0xC($16);
    andi       $2, $3, 0x2;
    beqz       $2, L00130A90;
    addiu     $2, $0, 0x1;
    addiu      $3, $16, 0x43;
    sw         $2, 0x14($16);
    sw         $3, 0x10($16);
    b          L00130B8C;
    sw        $3, 0x0($16);
    nop;
  L00130A90:
    lh         $5, 0xE($16);
    bltz       $5, L00130AB8;
    ori       $2, $3, 0x800;
    lw         $4, 0x54($16);
    jal        FstatR_130310;
    daddu     $6, $29, $0;
    bgez       $2, L00130AC8;
    lw        $2, 0x4($29);
    lhu        $3, 0xC($16);
    ori        $2, $3, 0x800;
  L00130AB8:
    daddu      $18, $0, $0;
    sh         $2, 0xC($16);
    b          L00130B0C;
    addiu     $17, $0, 0x400;
  L00130AC8:
    ori        $4, $0, 0x8000;
    addiu      $17, $0, 0x400;
    andi       $2, $2, 0xF000;
    xori       $3, $2, 0x2000;
    bne        $2, $4, L00130B00;
    sltiu     $18, $3, 0x1;
    lui        $2, 0x13;
    lw         $3, 0x28($16);
    addiu      $2, $2, 0x4530;
    bne        $3, $2, L00130B04;
    lhu       $2, 0xC($16);
    sw         $17, 0x4C($16);
    b          L00130B08;
    ori       $2, $2, 0x400;
  L00130B00:
    lhu        $2, 0xC($16);
  L00130B04:
    ori        $2, $2, 0x800;
  L00130B08:
    sh         $2, 0xC($16);
  L00130B0C:
    lw         $4, 0x54($16);
    jal        MallocR_1310d0;
    addiu     $5, $0, 0x400;
    daddu      $5, $2, $0;
    bnez       $5, L00130B48;
    lhu       $2, 0xC($16);
    addiu      $4, $16, 0x43;
    addiu      $3, $0, 0x1;
    sw         $4, 0x10($16);
    ori        $2, $2, 0x2;
    sw         $3, 0x14($16);
    sh         $2, 0xC($16);
    b          L00130B8C;
    sw        $4, 0x0($16);
    nop;
  L00130B48:
    lui        $3, 0x13;
    lw         $4, 0x54($16);
    addiu      $3, $3, -0x788;
    ori        $2, $2, 0x80;
    sw         $5, 0x10($16);
    sw         $3, 0x3C($4);
    sh         $2, 0xC($16);
    sw         $17, 0x14($16);
    beqz       $18, L00130B8C;
    sw        $5, 0x0($16);
    jal        IsattyStub_116d50;
    lh        $4, 0xE($16);
    beql       $2, $0, L00130B90;
    ld        $16, 0x70($29);
    lhu        $2, 0xC($16);
    ori        $2, $2, 0x1;
    sh         $2, 0xC($16);
  L00130B8C:
    ld         $16, 0x70($29);
  L00130B90:
    ld         $17, 0x78($29);
    ld         $18, 0x80($29);
    ld         $31, 0x88($29);
    jr         $31;
    addiu     $29, $29, 0x90;
}
