#include "types.h"

extern void MpegParseSliceHeader_10f058(void);
extern void IpuSyncIfBusy_10de98(void);
extern void MpegInvokeNodataCallback_1113b8(void);
extern void IpuStopDmaAndReset_115928(void);
extern void MpegIpuErrorReset_1159c8(void);
extern void IpuShowBits_10dd70(void);
extern void IpuDecodeMbAddrInc_10d828(void);
extern void MpegReportError_115a90(void);
extern void IpuDecodeMacroblock_10d2d0(void);
extern void MpegSkippedMacroblock_10ded8(void);
extern void MpegMotionCompensateMaybe_10bea0(void);
extern void MpegReconstructMacroblockMaybe_10c578(void);

asm void MpegDecodeSlices_10c9d8(void)
{
    .set noreorder;
    addiu      $29, $29, -0xE0;
    sd         $22, 0xC0($29);
    addiu      $6, $29, 0x40;
    sd         $16, 0x60($29);
    daddu      $22, $5, $0;
    daddu      $16, $4, $0;
    sw         $0, 0x40($29);
    sw         $0, 0x44($29);
    addiu      $7, $29, 0x44;
    daddu      $8, $29, $0;
    sd         $31, 0xD0($29);
    sd         $21, 0xB0($29);
    sd         $20, 0xA0($29);
    sd         $19, 0x90($29);
    sd         $18, 0x80($29);
    jal        MpegParseSliceHeader_10f058;
    sd        $17, 0x70($29);
    bnez       $2, L0010CCE0;
    ld        $31, 0xD0($29);
    sw         $0, 0x12C($16);
  L0010CA28:
    lw         $2, 0x40($29);
    slt        $2, $2, $22;
    bnel       $2, $0, L0010CA40;
    lw        $2, 0x820($16);
    b          L0010CCDC;
    daddu     $2, $0, $0;
  L0010CA40:
    addiu      $3, $0, 0x140;
    daddu      $4, $16, $0;
    addiu      $21, $0, 0x1;
    mult       $5, $2, $3;
    addu       $2, $5, $16;
    jal        IpuSyncIfBusy_10de98;
    sw        $0, 0x6DC($2);
    lui        $2, (0x1000B020 >> 16);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    lw         $3, 0x0($2);
    beqz       $3, L0010CAF4;
    lui       $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x4000;
    bnez       $3, L0010CAF8;
    lui       $2, (0x10002020 >> 16);
    lui        $20, (0x1000B420 >> 16);
    lui        $19, (0x1000B400 >> 16);
    lui        $18, (0x1000B020 >> 16);
    lui        $17, (0x10002010 >> 16);
    ori        $20, $20, (0x1000B420 & 0xFFFF);
    ori        $19, $19, (0x1000B400 & 0xFFFF);
    ori        $18, $18, (0x1000B020 & 0xFFFF);
    ori        $17, $17, (0x10002010 & 0xFFFF);
    nop;
  L0010CAA8:
    lw         $2, 0x0($20);
    bnel       $2, $0, L0010CAD0;
    lw        $2, 0x878($16);
    lw         $2, 0x0($19);
    andi       $2, $2, 0x100;
    bnel       $2, $0, L0010CAD0;
    lw        $2, 0x878($16);
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($16);
    lw         $2, 0x878($16);
  L0010CAD0:
    bnez       $2, L0010CB38;
    nop;
    lw         $2, 0x0($18);
    beqz       $2, L0010CAF8;
    lui       $2, (0x10002020 >> 16);
    lw         $2, 0x0($17);
    andi       $2, $2, 0x4000;
    beqz       $2, L0010CAA8;
    nop;
  L0010CAF4:
    lui        $2, (0x10002020 >> 16);
  L0010CAF8:
    lui        $3, (0x10002030 >> 16);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010CB48;
    sw        $2, 0x848($16);
    andi       $3, $5, 0x1F;
    beqz       $3, L0010CB30;
    addiu     $2, $0, 0x20;
    b          L0010CB4C;
    subu      $2, $2, $3;
  L0010CB30:
    b          L0010CB4C;
    daddu     $2, $0, $0;
  L0010CB38:
    jal        IpuStopDmaAndReset_115928;
    nop;
    b          L0010CB74;
    daddu     $2, $0, $0;
  L0010CB48:
    addiu      $2, $0, 0x20;
  L0010CB4C:
    sw         $2, 0x84C($16);
    lui        $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x4000;
    beqz       $3, L0010CB70;
    daddu     $4, $16, $0;
    jal        MpegIpuErrorReset_1159c8;
    daddu     $21, $0, $0;
  L0010CB70:
    daddu      $2, $21, $0;
  L0010CB74:
    bnel       $2, $0, L0010CB90;
    lw        $2, 0x44($29);
    lw         $4, 0x878($16);
    addiu      $3, $0, 0x4;
    addiu      $2, $0, 0x2;
    b          L0010CCDC;
    movn      $2, $3, $4;
  L0010CB90:
    bnez       $2, L0010CBDC;
    lw        $2, 0x40($29);
    daddu      $4, $16, $0;
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x17;
    beql       $2, $0, L0010CBBC;
    sw        $0, 0x12C($16);
    lw         $2, 0x12C($16);
    beqz       $2, L0010CBC4;
    nop;
    sw         $0, 0x12C($16);
  L0010CBBC:
    b          L0010CCDC;
    addiu     $2, $0, 0x3;
  L0010CBC4:
    jal        IpuDecodeMbAddrInc_10d828;
    daddu     $4, $16, $0;
    lw         $3, 0x12C($16);
    bnez       $3, L0010CC38;
    sw        $2, 0x44($29);
    lw         $2, 0x40($29);
  L0010CBDC:
    slt        $2, $2, $22;
    bnez       $2, L0010CC00;
    lw        $3, 0x44($29);
    lui        $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6150;
    b          L0010CCDC;
    addiu     $2, $0, 0x2;
  L0010CC00:
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0010CC44;
    addiu     $18, $29, 0x20;
    addiu      $17, $29, 0x30;
    daddu      $4, $16, $0;
    addiu      $5, $29, 0x48;
    addiu      $6, $29, 0x4C;
    addiu      $7, $29, 0x50;
    daddu      $8, $29, $0;
    daddu      $9, $18, $0;
    jal        IpuDecodeMacroblock_10d2d0;
    daddu     $10, $17, $0;
    bnez       $2, L0010CC68;
    lw        $5, 0x40($29);
  L0010CC38:
    sw         $0, 0x12C($16);
    b          L0010CCDC;
    addiu     $2, $0, 0x1;
  L0010CC44:
    daddu      $4, $16, $0;
    daddu      $5, $29, $0;
    addiu      $6, $29, 0x4C;
    daddu      $7, $18, $0;
    jal        MpegSkippedMacroblock_10ded8;
    addiu     $8, $29, 0x48;
    beqz       $2, L0010CC90;
    addiu     $17, $29, 0x30;
    lw         $5, 0x40($29);
  L0010CC68:
    daddu      $10, $18, $0;
    lw         $6, 0x44($29);
    daddu      $11, $17, $0;
    lw         $7, 0x48($29);
    daddu      $4, $16, $0;
    lw         $8, 0x4C($29);
    jal        MpegMotionCompensateMaybe_10bea0;
    daddu     $9, $29, $0;
    bnez       $2, L0010CC9C;
    lw        $4, 0x40($29);
  L0010CC90:
    sw         $0, 0x12C($16);
    b          L0010CCDC;
    addiu     $2, $0, 0x2;
  L0010CC9C:
    beql       $4, $0, L0010CCBC;
    lw        $2, 0x820($16);
    lw         $5, 0x820($16);
    daddu      $4, $16, $0;
    jal        MpegReconstructMacroblockMaybe_10c578;
    xori      $5, $5, 0x1;
    lw         $4, 0x40($29);
    lw         $2, 0x820($16);
  L0010CCBC:
    addiu      $4, $4, 0x1;
    lw         $3, 0x44($29);
    xori       $2, $2, 0x1;
    sw         $4, 0x40($29);
    addiu      $3, $3, -0x1;
    sw         $2, 0x820($16);
    b          L0010CA28;
    sw        $3, 0x44($29);
  L0010CCDC:
    ld         $31, 0xD0($29);
  L0010CCE0:
    ld         $22, 0xC0($29);
    ld         $21, 0xB0($29);
    ld         $20, 0xA0($29);
    ld         $19, 0x90($29);
    ld         $18, 0x80($29);
    ld         $17, 0x70($29);
    ld         $16, 0x60($29);
    jr         $31;
    addiu     $29, $29, 0xE0;
}

