#include "types.h"

extern void AabbLoadToVu_13bfc0(void);
extern void AabbPlaneDistances_13bf50(void);

asm void AabbInFrustum_13be60(void)
{
    .set noreorder;
    addiu      $29, $29, -0x50;
    sd         $31, 0x20($29);
    sq         $17, 0x10($29);
    sq         $16, 0x0($29);
    daddu      $17, $6, $0;
    jal        AabbLoadToVu_13bfc0;
    daddu     $16, $7, $0;
    daddu      $6, $17, $0;
    addiu      $4, $29, 0x40;
    jal        AabbPlaneDistances_13bf50;
    addiu     $5, $29, 0x30;
    lwc1       $f0, 0x40($29);
    lwc1       $f1, 0x30($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1tl      L0013BF38;
    daddu     $2, $0, $0;
    lwc1       $f0, 0x44($29);
    lwc1       $f1, 0x34($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1t       L0013BEEC;
    nop;
    lwc1       $f0, 0x48($29);
    lwc1       $f1, 0x38($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1t       L0013BEEC;
    nop;
    lwc1       $f0, 0x4C($29);
    lwc1       $f1, 0x3C($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1fl      L0013BEF8;
    daddu     $6, $16, $0;
  L0013BEEC:
    daddu      $2, $0, $0;
    b          L0013BF38;
    nop;
  L0013BEF8:
    addiu      $4, $29, 0x40;
    jal        AabbPlaneDistances_13bf50;
    addiu     $5, $29, 0x30;
    lwc1       $f0, 0x40($29);
    lwc1       $f1, 0x30($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1tl      L0013BF38;
    daddu     $2, $0, $0;
    lwc1       $f0, 0x44($29);
    lwc1       $f1, 0x34($29);
    neg.s      $f0, $f0;
    c.le.s     $f1, $f0;
    bc1fl      L0013BF38;
    addiu     $2, $0, 0x1;
    daddu      $2, $0, $0;
  L0013BF38:
    ld         $31, 0x20($29);
    lq         $17, 0x10($29);
    lq         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x50;
}

