#include "types.h"
extern void InitTLBThunk_1200b8(s32 code);
extern void _Exit(s32 code);

asm void KernelExit_120d18(s32 code)
{
    .set noreorder;
    addiu      $29, $29, -0x20;
    sd         $16, 0x0($29);
    sd         $31, 0x10($29);
    jal        InitTLBThunk_1200b8;
    daddu     $16, $4, $0;
    daddu      $4, $16, $0;
    ld         $31, 0x10($29);
    ld         $16, 0x0($29);
    j          _Exit;
    addiu     $29, $29, 0x20;
}
