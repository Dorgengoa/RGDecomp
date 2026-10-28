#include "types.h"

extern void KernelSetArgvMaybe_120b40(void);
extern void InitTLBThunk_1200b8(void);
extern void _LoadExecPS2(void);

asm void LoadExecPS2_120cd0(void)
{
    .set noreorder;
    addiu      $29, $29, -0x30;
    sd         $17, 0x10($29);
    sd         $16, 0x0($29);
    sd         $31, 0x20($29);
    jal        KernelSetArgvMaybe_120b40;
    daddu     $17, $5, $0;
    jal        InitTLBThunk_1200b8;
    daddu     $16, $2, $0;
    lui        $2, 0x44;
    daddu      $4, $16, $0;
    lw         $6, 0x6640($2);
    daddu      $5, $17, $0;
    ld         $31, 0x20($29);
    ld         $17, 0x10($29);
    addiu      $6, $6, 0x4;
    ld         $16, 0x0($29);
    j          _LoadExecPS2;
    addiu     $29, $29, 0x30;
}
