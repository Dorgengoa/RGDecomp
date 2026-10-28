#include "types.h"

extern void MpegInvokeCallback_111340(void);
extern void MpegDefaultErrorPrint_115918(void);

asm void MpegReportError_115a90(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $31, 0x10($29);
    lw         $3, 0x868($4);
    beqz       $3, L00115AD0;
    nop;
    beqz       $4, L00115AD0;
    nop;
    lw         $2, 0xC($4);
    beqz       $2, L00115AD0;
    daddu     $4, $3, $0;
    sw         $5, 0x4($29);
    sw         $0, 0x0($29);
    jal        MpegInvokeCallback_111340;
    daddu     $5, $29, $0;
    b          L00115ADC;
    ld        $31, 0x10($29);
  L00115AD0:
    jal        MpegDefaultErrorPrint_115918;
    daddu     $4, $5, $0;
    ld         $31, 0x10($29);
  L00115ADC:
    jr         $31;
    addiu     $29, $29, 0x20;
}
