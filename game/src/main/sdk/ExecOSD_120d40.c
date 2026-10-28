#include "types.h"

extern void KernelSetArgvMaybe_120b40(void);
extern void InitTLBThunk_1200b8(void);
extern void _ExecOSD(void);

asm void ExecOSD_120d40(void)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    daddu      $6, $5, $0;
    sd         $16, 0x0($29);
    daddu      $16, $4, $0;
    sd         $31, 0x10($29);
    lui        $4, 0x45;
    daddu      $5, $16, $0;
    jal        KernelSetArgvMaybe_120b40;
    addiu     $4, $4, 0x6CD0;
    jal        InitTLBThunk_1200b8;
    nop;
    lui        $2, 0x44;
    daddu      $4, $16, $0;
    lw         $5, 0x6640($2);
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    addiu      $5, $5, 0x4;
    j          _ExecOSD;
    addiu     $29, $29, 0x20;
}
