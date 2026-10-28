#include "types.h"

extern void MpegDemuxPssRing_115340(void);

asm void MpegDemuxPss_115720(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    daddu      $7, $0, $0;
    sd         $31, 0x0($29);
    jal        MpegDemuxPssRing_115340;
    addiu     $8, $0, -0x1;
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
