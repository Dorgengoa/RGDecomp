#include "types.h"

extern void IpuRestartDma_115d00(void);

asm void MpegDefaultCbRestartDma_111780(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lw         $4, 0x40($4);
    jal        IpuRestartDma_115d00;
    addiu     $4, $4, 0x68;
    ld         $31, 0x0($29);
    addiu      $2, $0, 0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
