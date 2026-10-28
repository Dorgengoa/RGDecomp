#include "types.h"

extern void MpegReportErrorFmt_115ae8(void);
extern void MpegMotionPredictMaybe_10b798(void);
extern void MpegKickSprDmaMaybe_10e148(void);

asm void MpegMotionCompensateMaybe_10bea0(void)
{
    .set noreorder;
    addiu      $29, $29, -0xB0;
    sd         $30, 0x90($29);
    sd         $23, 0x80($29);
    daddu      $30, $6, $0;
    sd         $22, 0x70($29);
    sd         $21, 0x60($29);
    sd         $16, 0x10($29);
    daddu      $21, $7, $0;
    sd         $31, 0xA0($29);
    daddu      $16, $4, $0;
    sd         $20, 0x50($29);
    andi       $3, $21, 0x1;
    sd         $19, 0x40($29);
    sd         $18, 0x30($29);
    sd         $17, 0x20($29);
    lw         $2, 0x13C($16);
    sw         $3, 0x0($29);
    div $5, $2;
    beql       $2, $0, L0010BEF0;
        .word 0x000001CD;
  L0010BEF0:
    lw         $2, 0x0($29);
    mfhi       $3;
    mflo       $23;
    daddu      $22, $3, $0;
    sll        $6, $23, 4;
    beqz       $2, L0010BF50;
    sll       $5, $22, 4;
    lw         $4, 0x820($16);
    addiu      $17, $16, 0x6D8;
    addiu      $18, $16, 0x6D4;
    addiu      $19, $16, 0x6D0;
    addiu      $20, $16, 0x6C8;
  L0010BF20:
    lui        $2, (0x1000D400 >> 16);
    ori        $2, $2, (0x1000D400 & 0xFFFF);
    lw         $3, 0x0($2);
    srl        $3, $3, 8;
    andi       $3, $3, 0x1;
    bnez       $3, L0010BF20;
    nop;
    addiu      $2, $0, 0x140;
    mult       $3, $4, $2;
    addu       $2, $3, $17;
    b          L0010BFE4;
    sw        $0, 0x0($2);
  L0010BF50:
    addiu      $2, $8, -0x1;
    sltiu      $2, $2, 0x3;
    bnez       $2, L0010BF84;
    daddu     $4, $16, $0;
    lui        $5, 0x45;
    daddu      $6, $8, $0;
    addiu      $5, $5, 0x60F0;
    jal        MpegReportErrorFmt_115ae8;
    daddu     $4, $16, $0;
    addiu      $3, $0, 0x1;
    daddu      $2, $0, $0;
    b          L0010C0C0;
    sw        $3, 0x12C($16);
  L0010BF84:
    jal        MpegMotionPredictMaybe_10b798;
    daddu     $7, $21, $0;
    lui        $3, (0x1000D400 >> 16);
    addiu      $17, $16, 0x6D8;
    addiu      $18, $16, 0x6D4;
    addiu      $19, $16, 0x6D0;
    addiu      $20, $16, 0x6C8;
    ori        $3, $3, (0x1000D400 & 0xFFFF);
    nop;
  L0010BFA8:
    lw         $2, 0x0($3);
    srl        $2, $2, 8;
    andi       $2, $2, 0x1;
    nop;
    nop;
    bnez       $2, L0010BFA8;
    nop;
    jal        MpegKickSprDmaMaybe_10e148;
    daddu     $4, $16, $0;
    lw         $2, 0x820($16);
    addiu      $3, $0, 0x140;
    addiu      $4, $0, 0x1;
    mult       $5, $2, $3;
    addu       $2, $5, $17;
    sw         $4, 0x0($2);
  L0010BFE4:
    addiu      $2, $0, 0x1;
    bnel       $30, $2, L0010C014;
    lw        $2, 0x820($16);
    andi       $2, $21, 0x2;
    beqz       $2, L0010C010;
    addiu     $3, $0, 0x140;
    lw         $2, 0x820($16);
    mult       $4, $2, $3;
    addu       $2, $4, $18;
    b          L0010C024;
    sw        $30, 0x0($2);
  L0010C010:
    lw         $2, 0x820($16);
  L0010C014:
    addiu      $3, $0, 0x140;
    mult       $4, $2, $3;
    addu       $2, $4, $18;
    sw         $0, 0x0($2);
  L0010C024:
    lw         $2, 0x820($16);
    addiu      $7, $0, 0x140;
    lw         $5, 0x0($29);
    addiu      $3, $0, 0x3;
    mult       $4, $2, $7;
    addu       $2, $4, $19;
    sw         $5, 0x0($2);
    lw         $4, 0x184($16);
    bne        $4, $3, L0010C080;
    addiu     $2, $0, 0x2;
    lw         $4, 0x820($16);
    addiu      $6, $0, 0x180;
    lw         $5, 0x1D0($16);
    mult       $3, $4, $7;
    lw         $2, 0x10($5);
    addu       $4, $3, $20;
    lw         $3, 0x0($5);
    mult       $5, $22, $2;
    addu       $2, $5, $23;
    mult       $2, $2, $6;
    addu       $3, $3, $2;
    b          L0010C0BC;
    sw        $3, 0x0($4);
  L0010C080:
    bnel       $4, $2, L0010C08C;
    lw        $2, 0x1E0($16);
    lw         $2, 0x1F0($16);
  L0010C08C:
    lw         $3, 0x10($2);
    addiu      $6, $0, 0x180;
    lw         $4, 0x820($16);
    addiu      $5, $0, 0x140;
    mult       $7, $22, $3;
    lw         $2, 0x0($2);
    addu       $3, $7, $23;
    mult       $7, $4, $5;
    mult       $3, $3, $6;
    addu       $4, $7, $20;
    addu       $2, $2, $3;
    sw         $2, 0x0($4);
  L0010C0BC:
    addiu      $2, $0, 0x1;
  L0010C0C0:
    ld         $31, 0xA0($29);
    ld         $30, 0x90($29);
    ld         $23, 0x80($29);
    ld         $22, 0x70($29);
    ld         $21, 0x60($29);
    ld         $20, 0x50($29);
    ld         $19, 0x40($29);
    ld         $18, 0x30($29);
    ld         $17, 0x20($29);
    ld         $16, 0x10($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
}

