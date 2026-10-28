#include "types.h"

extern void IpuStopDma_115c18(void);

asm void MpegDefaultCbStopDma_111758(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    lw         $4, 0x40($4);
    jal        IpuStopDma_115c18;
    addiu     $4, $4, 0x68;
    ld         $31, 0x0($29);
    addiu      $2, $0, 0x1;
    jr         $31;
    addiu     $29, $29, 0x10;
}
