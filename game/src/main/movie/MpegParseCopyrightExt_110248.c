#include "types.h"

extern void IpuGetBits_10dc88(void);

asm void MpegParseCopyrightExt_110248(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $5, $0, 0x1;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        IpuGetBits_10dc88;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x8;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x7;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x14;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x16;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x16;
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x20;
}
