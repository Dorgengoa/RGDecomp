#include "types.h"

extern void sceSnprintfMaybe_1191d0(void);
extern void MpegReportError_115a90(void);

asm void MpegReportErrorFmt_115ae8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x120;
    daddu      $7, $6, $0;
    sd         $16, 0x100($29);
    daddu      $6, $5, $0;
    daddu      $16, $4, $0;
    addiu      $5, $0, 0x100;
    sd         $31, 0x110($29);
    jal        sceSnprintfMaybe_1191d0;
    daddu     $4, $29, $0;
    daddu      $4, $16, $0;
    jal        MpegReportError_115a90;
    daddu     $5, $29, $0;
    ld         $31, 0x110($29);
    ld         $16, 0x100($29);
    jr         $31;
    addiu     $29, $29, 0x120;
}
