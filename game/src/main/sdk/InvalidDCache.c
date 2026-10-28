#include "types.h"

extern void DisableIntr_120660(void);
extern void _sceIDC(s32, s32);
extern void EnableIntr_1206b0(void);

/* Sibling of SyncDCache (calls _sceIDC instead of _sceSDC). */

asm void InvalidDCache(void)
{
    .set noreorder;
    addiu $29, $29, -0x40;
    sd    $18, 0x20($29);
    sd    $17, 0x10($29);
    daddu $18, $4, $0;
    sd    $31, 0x30($29);
    daddu $17, $5, $0;
    sd    $16, 0x0($29);
    mfc0  $16, $12;
    lui   $2, (0x10000 >> 16);
    and   $16, $16, $2;
    beqz  $16, L00117010;
    nop;
    jal   DisableIntr_120660;
    nop;
L00117010:
    lui   $4, (0xFFFFFFC0 >> 16);
    ori   $4, $4, (0xFFFFFFC0 & 0xFFFF);
    and   $5, $17, $4;
    jal   _sceIDC;
    and   $4, $18, $4;
    beqz  $16, L00117040;
    ld    $31, 0x30($29);
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    j     EnableIntr_1206b0;
    addiu $29, $29, 0x40;
L00117040:
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    jr    $31;
    addiu $29, $29, 0x40;
}
