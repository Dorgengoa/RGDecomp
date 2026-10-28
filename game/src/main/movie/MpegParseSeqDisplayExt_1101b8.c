#include "types.h"

extern void IpuGetBits_10dc88(void);

asm void MpegParseSeqDisplayExt_1101b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $5, $0, 0x3;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        IpuGetBits_10dc88;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    beqz       $2, L00110208;
    daddu     $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x8;
    sw         $2, 0x154($16);
  L00110208:
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0xE;
    sw         $2, 0x158($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0xE;
    sw         $2, 0x15C($16);
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
