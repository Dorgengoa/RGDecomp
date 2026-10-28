#include "types.h"

extern void MpegReportError_115a90(void);
extern void MpegInvokeCallback_111340(void);
extern void DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);

asm void MpegIpuErrorReset_1159c8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    lui        $5, 0x45;
    sd         $16, 0x20($29);
    addiu      $5, $5, 0x6640;
    sd         $31, 0x30($29);
    jal        MpegReportError_115a90;
    daddu     $16, $4, $0;
    addiu      $2, $0, 0x2;
    lw         $4, 0x868($16);
    sw         $2, 0x0($29);
    jal        MpegInvokeCallback_111340;
    daddu     $5, $29, $0;
    lui        $3, (0x10002010 >> 16);
    lui        $5, (0x40000000 >> 16);
    ori        $3, $3, (0x10002010 & 0xFFFF);
    lw         $4, 0x868($16);
    sw         $5, 0x0($3);
    addiu      $2, $0, 0x3;
    sw         $2, 0x0($29);
    jal        MpegInvokeCallback_111340;
    daddu     $5, $29, $0;
    jal        DisableIntr_120660;
    nop;
    lui        $6, (0x1000F520 >> 16);
    lui        $7, (0x1000F590 >> 16);
    ori        $6, $6, (0x1000F520 & 0xFFFF);
    lui        $8, (0x10000 >> 16);
    lw         $3, 0x0($6);
    ori        $7, $7, (0x1000F590 & 0xFFFF);
    lui        $4, (0x1000B000 >> 16);
    lui        $5, (0xFFFEFFFF >> 16);
    or         $3, $3, $8;
    ori        $4, $4, (0x1000B000 & 0xFFFF);
    sw         $3, 0x0($7);
    ori        $5, $5, (0xFFFEFFFF & 0xFFFF);
    sw         $0, 0x0($4);
    lw         $3, 0x0($6);
    and        $3, $3, $5;
    sw         $3, 0x0($7);
    beqz       $2, L00115A78;
    lui       $2, (0x1000B020 >> 16);
    jal        EnableIntr_1206b0;
    nop;
    lui        $2, (0x1000B020 >> 16);
  L00115A78:
    ld         $31, 0x30($29);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    ld         $16, 0x20($29);
    sw         $0, 0x0($2);
    jr         $31;
    addiu     $29, $29, 0x40;
}
