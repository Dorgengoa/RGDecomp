#include "types.h"

extern void StdioSinit_12f8b8(void);
extern void Fflush_12f590(void);

asm void Ftell_130370(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x8($29);
    lw         $3, 0x54($16);
    bnel       $3, $0, L001303A0;
    lw        $2, 0x38($3);
    lui        $2, 0x45;
    lw         $3, -0x67A8($2);
    sw         $3, 0x54($16);
    lw         $2, 0x38($3);
    nop;
  L001303A0:
    bnel       $2, $0, L001303B4;
    lw        $2, 0x28($16);
    jal        StdioSinit_12f8b8;
    daddu     $4, $3, $0;
    lw         $2, 0x28($16);
  L001303B4:
    bnez       $2, L001303D0;
    addiu     $3, $0, 0x1D;
    lw         $4, 0x54($16);
    addiu      $2, $0, -0x1;
    b          L00130464;
    sw        $3, 0x0($4);
    nop;
  L001303D0:
    jal        Fflush_12f590;
    daddu     $4, $16, $0;
    lhu        $3, 0xC($16);
    andi       $2, $3, 0x1000;
    beql       $2, $0, L001303F0;
    lw        $2, 0x28($16);
    b          L00130414;
    lw        $5, 0x50($16);
  L001303F0:
    daddu      $5, $0, $0;
    lw         $4, 0x1C($16);
    jalr $31, $2;
    addiu     $6, $0, 0x1;
    addiu      $3, $0, -0x1;
    daddu      $5, $2, $0;
    beql       $5, $3, L00130468;
    ld        $16, 0x0($29);
    lhu        $3, 0xC($16);
  L00130414:
    andi       $2, $3, 0x4;
    beqz       $2, L00130440;
    andi      $2, $3, 0x8;
    lw         $2, 0x4($16);
    lw         $3, 0x30($16);
    beqz       $3, L00130460;
    dsubu     $5, $5, $2;
    lw         $2, 0x3C($16);
    b          L00130460;
    dsubu     $5, $5, $2;
    nop;
  L00130440:
    beqz       $2, L00130464;
    daddu     $2, $5, $0;
    lw         $3, 0x0($16);
    beql       $3, $0, L00130468;
    ld        $16, 0x0($29);
    lw         $2, 0x10($16);
    subu       $2, $3, $2;
    daddu      $5, $5, $2;
  L00130460:
    daddu      $2, $5, $0;
  L00130464:
    ld         $16, 0x0($29);
  L00130468:
    ld         $31, 0x8($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

