#include "types.h"

extern void MpegDecodeSlices_10c9d8(void);
extern void IpuSyncIfBusy_10de98(void);
extern void MpegInvokeNodataCallback_1113b8(void);
extern void IpuStopDmaAndReset_115928(void);
extern void MpegIpuErrorReset_1159c8(void);
extern void MpegReconstructMacroblockMaybe_10c578(void);
extern void MpegReportError_115a90(void);

asm void MpegDecodePictureBodyMaybe_10c798(void)
{
    .set noreorder;
    addiu      $29, $29, -0x80;
    sd         $19, 0x30($29);
    sd         $18, 0x20($29);
    addiu      $19, $0, 0x1;
    sd         $17, 0x10($29);
    addiu      $18, $0, 0x3;
    sd         $16, 0x0($29);
    daddu      $17, $4, $0;
    sd         $31, 0x70($29);
    sd         $22, 0x60($29);
    sd         $21, 0x50($29);
    sd         $20, 0x40($29);
    sw         $0, 0x820($17);
    lw         $2, 0x140($17);
    lw         $4, 0x13C($17);
    lw         $3, 0x184($17);
    mult       $16, $4, $2;
    sw         $0, 0x824($17);
    xori       $3, $3, 0x3;
    sra        $2, $16, 1;
    movn       $16, $2, $3;
    nop;
  L0010C7F0:
    daddu      $4, $17, $0;
  L0010C7F4:
    jal        MpegDecodeSlices_10c9d8;
    daddu     $5, $16, $0;
    daddu      $21, $2, $0;
    beq        $21, $19, L0010C7F4;
    daddu     $4, $17, $0;
    beq        $21, $18, L0010C7F0;
    nop;
    jal        IpuSyncIfBusy_10de98;
    addiu     $22, $0, 0x1;
    jal        IpuSyncIfBusy_10de98;
    daddu     $4, $17, $0;
    lui        $2, (0x1000B020 >> 16);
    ori        $2, $2, (0x1000B020 & 0xFFFF);
    lw         $3, 0x0($2);
    beqz       $3, L0010C8B4;
    lui       $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x4000;
    bnez       $3, L0010C8B8;
    lui       $2, (0x10002020 >> 16);
    lui        $20, (0x1000B420 >> 16);
    lui        $19, (0x1000B400 >> 16);
    lui        $18, (0x1000B020 >> 16);
    lui        $16, (0x10002010 >> 16);
    ori        $20, $20, (0x1000B420 & 0xFFFF);
    ori        $19, $19, (0x1000B400 & 0xFFFF);
    ori        $18, $18, (0x1000B020 & 0xFFFF);
    ori        $16, $16, (0x10002010 & 0xFFFF);
  L0010C868:
    lw         $2, 0x0($20);
    bnel       $2, $0, L0010C890;
    lw        $2, 0x878($17);
    lw         $2, 0x0($19);
    andi       $2, $2, 0x100;
    bnel       $2, $0, L0010C890;
    lw        $2, 0x878($17);
    jal        MpegInvokeNodataCallback_1113b8;
    lw        $4, 0x868($17);
    lw         $2, 0x878($17);
  L0010C890:
    bnez       $2, L0010C8F8;
    nop;
    lw         $2, 0x0($18);
    beqz       $2, L0010C8B8;
    lui       $2, (0x10002020 >> 16);
    lw         $2, 0x0($16);
    andi       $2, $2, 0x4000;
    beqz       $2, L0010C868;
    nop;
  L0010C8B4:
    lui        $2, (0x10002020 >> 16);
  L0010C8B8:
    lui        $3, (0x10002030 >> 16);
    ori        $2, $2, (0x10002020 & 0xFFFF);
    ori        $3, $3, (0x10002030 & 0xFFFF);
    lw         $5, 0x0($2);
    ld         $4, 0x0($3);
    dsll32     $2, $4, 0;
    dsra32     $2, $2, 0;
    bgez       $4, L0010C908;
    sw        $2, 0x848($17);
    andi       $3, $5, 0x1F;
    beqz       $3, L0010C8F0;
    addiu     $2, $0, 0x20;
    b          L0010C90C;
    subu      $2, $2, $3;
  L0010C8F0:
    b          L0010C90C;
    daddu     $2, $0, $0;
  L0010C8F8:
    jal        IpuStopDmaAndReset_115928;
    nop;
    b          L0010C934;
    daddu     $2, $0, $0;
  L0010C908:
    addiu      $2, $0, 0x20;
  L0010C90C:
    sw         $2, 0x84C($17);
    lui        $2, (0x10002010 >> 16);
    ori        $2, $2, (0x10002010 & 0xFFFF);
    lw         $3, 0x0($2);
    andi       $3, $3, 0x4000;
    beqz       $3, L0010C930;
    daddu     $4, $17, $0;
    jal        MpegIpuErrorReset_1159c8;
    daddu     $22, $0, $0;
  L0010C930:
    daddu      $2, $22, $0;
  L0010C934:
    bnez       $2, L0010C950;
    lui       $3, (0x1000D400 >> 16);
    lw         $2, 0x878($17);
    bnez       $2, L0010C9B0;
    addiu     $2, $0, 0x4;
    addiu      $21, $0, 0x2;
    lui        $3, (0x1000D400 >> 16);
  L0010C950:
    addiu      $16, $21, -0x1;
    sltiu      $18, $21, 0x1;
    ori        $3, $3, (0x1000D400 & 0xFFFF);
    nop;
  L0010C960:
    lw         $2, 0x0($3);
    srl        $2, $2, 8;
    andi       $2, $2, 0x1;
    nop;
    nop;
    bnez       $2, L0010C960;
    nop;
    bnez       $21, L0010C998;
    sltiu     $2, $16, 0x2;
    lw         $5, 0x820($17);
    daddu      $4, $17, $0;
    jal        MpegReconstructMacroblockMaybe_10c578;
    sltiu     $5, $5, 0x1;
    sltiu      $2, $16, 0x2;
  L0010C998:
    beqz       $2, L0010C9AC;
    daddu     $4, $17, $0;
    lui        $5, 0x45;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6130;
  L0010C9AC:
    daddu      $2, $18, $0;
  L0010C9B0:
    ld         $31, 0x70($29);
    ld         $22, 0x60($29);
    ld         $21, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x80;
}

