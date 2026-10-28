#include "types.h"

extern void MpegReportError_115a90(void);

asm void MpegWorkAreaAlloc_1116d0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $8, $4, $0;
    sd         $31, 0x0($29);
    beql       $7, $0, L001116E4;
        .word 0x000001CD;
  L001116E4:
    lw         $2, 0x8($5);
    lw         $4, 0x4($5);
    addu       $2, $2, $7;
    lw         $3, 0x0($5);
    addiu      $2, $2, -0x1;
    divu $2, $7;
    addu       $3, $3, $4;
    mflo       $2;
    mult       $2, $2, $7;
    addu       $4, $2, $6;
    sltu       $3, $3, $4;
    bnel       $3, $0, L00111720;
    lui       $5, 0x45;
    b          L00111730;
    sw        $4, 0x8($5);
  L00111720:
    daddu      $4, $8, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6578;
    daddu      $2, $0, $0;
  L00111730:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}

