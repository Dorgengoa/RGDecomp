#include "types.h"

extern void RFU086_WaitEvnetFlag(void);

asm void SetTLBEntry_120028(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    addiu      $2, $4, -0xD;
    sltiu      $2, $2, 0x23;
    bnez       $2, L00120044;
    sd        $31, 0x0($29);
    b          L0012004C;
    addiu     $2, $0, -0x1;
  L00120044:
    jal        RFU086_WaitEvnetFlag;
    nop;
  L0012004C:
    ld         $31, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x10;
}
