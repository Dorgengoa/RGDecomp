#include "types.h"

extern void GetMemorySize(void);
extern void InitTLB32MB_1200f8(void);
extern void _InitTLB(void);

asm void InitTLB_1200b8(void)
{
    .set noreorder;
    addiu      $29, $29, -0x10;
    sd         $31, 0x0($29);
    jal        GetMemorySize;
    nop;
    lui        $3, (0x2000000 >> 16);
    bne        $2, $3, L001200E4;
    nop;
    jal        InitTLB32MB_1200f8;
    nop;
    b          L001200F0;
    ld        $31, 0x0($29);
  L001200E4:
    jal        _InitTLB;
    nop;
    ld         $31, 0x0($29);
  L001200F0:
    jr         $31;
    addiu     $29, $29, 0x10;
}
