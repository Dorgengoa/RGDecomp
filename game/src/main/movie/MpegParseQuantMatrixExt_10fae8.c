#include "types.h"

extern void IpuGetBits_10dc88(void);
extern void IpuSyncIfBusy_10ffc8(void);
extern void MpegReportError_115a90(void);

asm void MpegParseQuantMatrixExt_10fae8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $5, $0, 0x1;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        IpuGetBits_10dc88;
    daddu     $16, $4, $0;
    beqz       $2, L0010FB34;
    sw        $2, 0x850($16);
    jal        IpuSyncIfBusy_10ffc8;
    daddu     $4, $16, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x50000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    addiu      $5, $0, 0x1;
    sw         $3, 0x0($2);
    daddu      $4, $16, $0;
    sw         $3, 0x82C($16);
    jal        IpuSyncIfBusy_10ffc8;
    sw        $5, 0x828($16);
  L0010FB34:
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    beqz       $2, L0010FB78;
    sw        $2, 0x854($16);
    jal        IpuSyncIfBusy_10ffc8;
    daddu     $4, $16, $0;
    lui        $2, (0x10002000 >> 16);
    lui        $3, (0x58000000 >> 16);
    ori        $2, $2, (0x10002000 & 0xFFFF);
    lui        $4, (0x50000000 >> 16);
    sw         $3, 0x0($2);
    addiu      $5, $0, 0x1;
    sw         $4, 0x82C($16);
    daddu      $4, $16, $0;
    jal        IpuSyncIfBusy_10ffc8;
    sw        $5, 0x828($16);
  L0010FB78:
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    beqz       $2, L0010FB98;
    lui       $5, 0x45;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    addiu     $5, $5, 0x62A8;
  L0010FB98:
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    beqz       $2, L0010FBC4;
    ld        $31, 0x10($29);
    daddu      $4, $16, $0;
    lui        $5, 0x45;
    addiu      $5, $5, 0x62D0;
    ld         $16, 0x0($29);
    j          MpegReportError_115a90;
    addiu     $29, $29, 0x20;
  L0010FBC4:
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}

