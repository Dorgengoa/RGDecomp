#include "types.h"

extern void KernelSetArgvMaybe_120b40(void);
extern void InitTLBThunk_1200b8(void);
extern void ExecPS2_1161f0(void);

asm void ExecPS2_120c60(void)
{
    .set noreorder;
    addiu      $29, $29, -0x40;
    sd         $17, 0x10($29);
    daddu      $17, $4, $0;
    sd         $18, 0x20($29);
    sd         $16, 0x0($29);
    daddu      $18, $5, $0;
    daddu      $16, $6, $0;
    lui        $4, 0x45;
    daddu      $5, $16, $0;
    sd         $31, 0x30($29);
    addiu      $4, $4, 0x6CD0;
    jal        KernelSetArgvMaybe_120b40;
    daddu     $6, $7, $0;
    jal        InitTLBThunk_1200b8;
    nop;
    lui        $2, 0x44;
    daddu      $4, $17, $0;
    lw         $7, 0x6640($2);
    daddu      $5, $18, $0;
    daddu      $6, $16, $0;
    jal        ExecPS2_1161f0;
    addiu     $7, $7, 0x4;
    ld         $31, 0x30($29);
    ld         $18, 0x20($29);
    ld         $17, 0x10($29);
    ld         $16, 0x0($29);
    jr         $31;
    addiu     $29, $29, 0x40;
}
