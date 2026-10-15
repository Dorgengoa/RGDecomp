#include "types.h"

/* I-cache sync loop, sibling of _sceSDC (cache ops 0x10/0x16). */

asm void _sceIDC(void)
{
    .set noreorder;
    lui   $7, (0xFFFFF000 >> 16);
    daddu $6, $0, $0;
    ori   $7, $7, (0xFFFFF000 & 0xFFFF);
    nop;
L00116F40:
    sync;
    cache 0x10, 0x0($6);
    sync;
    mfc0  $2, $28;
    and   $2, $2, $7;
    addu  $2, $2, $6;
    sltu  $3, $5, $2;
    sltu  $2, $2, $4;
    bnez  $2, L00116F7C;
    nop;
    bnez  $3, L00116F7C;
    nop;
    sync;
    cache 0x16, 0x0($6);
    sync;
L00116F7C:
    sync;
    cache 0x10, 0x1($6);
    sync;
    mfc0  $2, $28;
    and   $2, $2, $7;
    addu  $2, $2, $6;
    sltu  $3, $5, $2;
    sltu  $2, $2, $4;
    bnez  $2, L00116FB8;
    nop;
    bnez  $3, L00116FB8;
    nop;
    sync;
    cache 0x16, 0x1($6);
    sync;
L00116FB8:
    sync;
    addiu $6, $6, 0x40;
    slti  $2, $6, 0x1000;
    bnez  $2, L00116F40;
    nop;
    jr    $31;
    nop;
}
