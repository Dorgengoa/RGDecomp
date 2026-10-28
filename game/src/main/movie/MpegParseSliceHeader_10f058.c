#include "types.h"

extern void IpuByteAlign_110168(void);
extern void IpuSkipBitsThunk2_10de00(void);
extern void IpuShowBits_10dd70(void);
extern void MpegReportErrorFmt_115ae8(void);
extern void IpuSkip32Bits_110160(void);
extern void IpuGetBits_10dc88(void);
extern void IpuDecodeMbAddrInc_10d828(void);
extern void MpegReportError_115a90(void);

asm void MpegParseSliceHeader_10f058(void)
{
    .set noreorder;
    addiu      $29, $29, -0x60;
    sd         $16, 0x0($29);
    sd         $20, 0x40($29);
    daddu      $16, $4, $0;
    sd         $19, 0x30($29);
    daddu      $20, $6, $0;
    sd         $18, 0x20($29);
    daddu      $19, $7, $0;
    sd         $17, 0x10($29);
    sd         $31, 0x50($29);
    daddu      $17, $8, $0;
    sw         $0, 0x12C($16);
    jal        IpuByteAlign_110168;
    addiu     $18, $0, 0x1;
    b          L0010F0A4;
    daddu     $4, $16, $0;
  L0010F098:
    jal        IpuSkipBitsThunk2_10de00;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
  L0010F0A4:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x18;
    beq        $2, $18, L0010F0C0;
    daddu     $4, $16, $0;
    lw         $2, 0x878($16);
    beqz       $2, L0010F098;
    nop;
  L0010F0C0:
    jal        IpuShowBits_10dd70;
    addiu     $5, $0, 0x20;
    daddu      $18, $2, $0;
    addiu      $2, $18, -0x101;
    sltiu      $2, $2, 0xAF;
    bnez       $2, L0010F0F4;
    lui       $5, 0x45;
    daddu      $4, $16, $0;
    addiu      $5, $5, 0x61F8;
    jal        MpegReportErrorFmt_115ae8;
    daddu     $6, $18, $0;
    b          L0010F1D8;
    addiu     $2, $0, 0x2;
  L0010F0F4:
    jal        IpuSkip32Bits_110160;
    daddu     $4, $16, $0;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x5;
    sw         $2, 0x1C4($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    beqz       $2, L0010F15C;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuSkipBitsThunk2_10de00;
    addiu     $5, $0, 0x7;
    b          L0010F14C;
    daddu     $4, $16, $0;
    nop;
  L0010F140:
    jal        IpuSkipBitsThunk2_10de00;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
  L0010F14C:
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    bnez       $2, L0010F140;
    daddu     $4, $16, $0;
  L0010F15C:
    jal        IpuDecodeMbAddrInc_10d828;
    daddu     $4, $16, $0;
    daddu      $6, $2, $0;
    sw         $6, 0x0($19);
    lw         $2, 0x12C($16);
    beqz       $2, L0010F18C;
    lui       $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x6220;
    b          L0010F1D8;
    addiu     $2, $0, 0x1;
  L0010F18C:
    lw         $2, 0x13C($16);
    andi       $3, $18, 0xFF;
    addiu      $3, $3, -0x1;
    addiu      $4, $0, 0x1;
    mult       $5, $3, $2;
    daddu      $2, $0, $0;
    addu       $3, $5, $6;
    addiu      $3, $3, -0x1;
    sw         $3, 0x0($20);
    sw         $4, 0x0($19);
    sw         $4, 0x1C0($16);
    sw         $0, 0x8($17);
    sw         $0, 0x14($17);
    sw         $0, 0x10($17);
    sw         $0, 0x4($17);
    sw         $0, 0x0($17);
    sw         $0, 0x1C($17);
    sw         $0, 0x18($17);
    sw         $0, 0xC($17);
  L0010F1D8:
    ld         $31, 0x50($29);
    ld         $20, 0x40($29);
    ld         $19, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x60;
}

