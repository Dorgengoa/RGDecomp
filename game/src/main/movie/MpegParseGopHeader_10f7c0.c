#include "types.h"

extern void IpuGetBits_10dc88(void);
extern void MpegParseExtUserData_10fdf8(void);

asm void MpegParseGopHeader_10f7c0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    addiu      $3, $0, 0x1;
    sd         $16, 0x0($29);
    addiu      $5, $0, 0x1;
    sd         $31, 0x10($29);
    daddu      $16, $4, $0;
    sw         $0, 0xFC($16);
    lw         $2, 0x860($16);
    sw         $3, 0x864($16);
    addiu      $2, $2, 0x1;
    jal        IpuGetBits_10dc88;
    sw        $2, 0x85C($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x5;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x6;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x6;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x6;
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    sw         $2, 0x1B4($16);
    daddu      $4, $16, $0;
    jal        IpuGetBits_10dc88;
    addiu     $5, $0, 0x1;
    sw         $2, 0x1B8($16);
    daddu      $4, $16, $0;
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    j          MpegParseExtUserData_10fdf8;
    addiu     $29, $29, 0x20;
}

