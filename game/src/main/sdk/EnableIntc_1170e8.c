#include "types.h"

extern void DisableIntr_120660(void);
extern void _EnableIntc(s32 cause);
extern s32 EnableIntr_1206b0(void);

asm void EnableIntc_1170e8(void)
{
    .set noreorder;
    addiu $29, $29, -0x30;
    sd    $17, 0x10($29);
    sd    $31, 0x20($29);
    daddu $17, $4, $0;
    sd    $16, 0x0($29);
    mfc0  $16, $12;
    lui   $2, (0x10000 >> 16);
    and   $16, $16, $2;
    beqz  $16, L00117118;
    nop;
    jal   DisableIntr_120660;
    nop;
L00117118:
    jal   _EnableIntc;
    daddu $4, $17, $0;
    daddu $17, $2, $0;
    sync;
    beqz  $16, L0011713C;
    daddu $2, $17, $0;
    jal   EnableIntr_1206b0;
    nop;
    daddu $2, $17, $0;
L0011713C:
    ld    $31, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x30;
}
