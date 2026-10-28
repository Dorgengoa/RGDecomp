#include "types.h"

extern void AddDmacHandler_2(void);
extern void EnableDmac_1171b8(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void MpegInvokeCallback_111340(void);
extern void MpegReportError_115a90(void);
extern void DisableDmac_117150(void);
extern void RemoveDmacHandler(void);

asm void MpegIpuCsc_112268(void)
{
    .set noreorder;
    addiu      $7, $0, 0x3FF;
    addiu      $29, $29, -0x80;
    div $6, $7;
    sd         $16, 0x40($29);
    lui        $2, (0xFFC00 >> 16);
    daddu      $16, $5, $0;
    ori        $2, $2, (0xFFC00 & 0xFFFF);
    lui        $3, (0xFFFFFFF >> 16);
    sd         $17, 0x50($29);
    ori        $3, $3, (0xFFFFFFF & 0xFFFF);
    sd         $31, 0x70($29);
    addu       $2, $16, $2;
    sd         $18, 0x60($29);
    and        $2, $2, $3;
    beql       $7, $0, L001122A8;
        .word 0x000001CD;
  L001122A8:
    lui        $3, (0x10002010 >> 16);
    sw         $6, 0x28($29);
    daddu      $17, $4, $0;
    sw         $2, 0x2C($29);
    addiu      $7, $29, 0x20;
    sw         $0, 0x24($29);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    sw         $0, 0x20($29);
    mflo       $8;
    addiu      $8, $8, 0x1;
    sw         $8, 0x30($29);
    nop;
  L001122D8:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bltz       $2, L001122D8;
    nop;
    lui        $5, 0x11;
    addiu      $4, $0, 0x3;
    addiu      $5, $5, 0x2900;
    jal        AddDmacHandler_2;
    daddu     $6, $0, $0;
    daddu      $18, $2, $0;
    addiu      $3, $0, 0x8;
    lui        $2, (0x1000E010 >> 16);
    addiu      $4, $0, 0x3;
    ori        $2, $2, (0x1000E010 & 0xFFFF);
    jal        EnableDmac_1171b8;
    sw        $3, 0x0($2);
    jal        DisableIntr_120660;
    nop;
    lui        $3, (0xFFFFFFF >> 16);
    lui        $4, (0x1000B010 >> 16);
    ori        $3, $3, (0xFFFFFFF & 0xFFFF);
    ori        $4, $4, (0x1000B010 & 0xFFFF);
    and        $3, $16, $3;
    lui        $5, (0x1000B020 >> 16);
    sw         $3, 0x0($4);
    ori        $5, $5, (0x1000B020 & 0xFFFF);
    ori        $3, $0, 0xFFC0;
    lui        $4, (0x1000B000 >> 16);
    sw         $3, 0x0($5);
    ori        $4, $4, (0x1000B000 & 0xFFFF);
    addiu      $3, $0, 0x100;
    sw         $3, 0x0($4);
    beqz       $2, L00112378;
    lui       $2, (0x10002000 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, (0x10002000 >> 16);
  L00112378:
    lui        $3, (0x700003FF >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    ori        $3, $3, (0x700003FF & 0xFFFF);
    sw         $3, 0x0($2);
    addiu      $6, $0, 0x4;
    lw         $4, 0x868($17);
    daddu      $5, $29, $0;
    jal        MpegInvokeCallback_111340;
    sw        $6, 0x0($29);
    lw         $4, 0x24($29);
    lw         $3, 0x30($29);
    nop;
  L001123A8:
    lw         $2, 0x20($29);
    slt        $2, $2, $3;
    nop;
    nop;
    nop;
    bnez       $2, L001123A8;
    nop;
    beqz       $4, L001123D8;
    daddu     $4, $17, $0;
    lui        $5, 0x45;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x65E8;
  L001123D8:
    lui        $3, (0x10002010 >> 16);
    ori        $3, $3, (0x10002010 & 0xFFFF);
  L001123E0:
    lw         $2, 0x0($3);
    nop;
    nop;
    nop;
    nop;
    bltz       $2, L001123E0;
    nop;
    jal        DisableDmac_117150;
    addiu     $4, $0, 0x3;
    daddu      $5, $18, $0;
    jal        RemoveDmacHandler;
    addiu     $4, $0, 0x3;
    ld         $31, 0x70($29);
    ld         $18, 0x60($29);
    ld         $17, 0x50($29);
    ld         $16, 0x40($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

