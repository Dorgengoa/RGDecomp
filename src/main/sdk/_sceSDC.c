#include "types.h"

/* D-cache sync loop. Same shape as _sceIDC (differs only in the `cache`
   op codes: 0x10/0x14 here vs 0x10/0x16 there). Naked asm void. */

asm void _sceSDC(void)
{
    .set noreorder;
    lui   $7, (0xFFFFF000 >> 16);
    daddu $6, $0, $0;
    ori   $7, $7, (0xFFFFF000 & 0xFFFF);
    nop;
L00116E00:
    sync;
    cache 0x10, 0x0($6);
    sync;
    mfc0  $2, $28;
    and   $2, $2, $7;
    addu  $2, $2, $6;
    sltu  $3, $5, $2;
    sltu  $2, $2, $4;
    bnez  $2, L00116E3C;
    nop;
    bnez  $3, L00116E3C;
    nop;
    sync;
    cache 0x14, 0x0($6);
    sync;
L00116E3C:
    sync;
    cache 0x10, 0x1($6);
    sync;
    mfc0  $2, $28;
    and   $2, $2, $7;
    addu  $2, $2, $6;
    sltu  $3, $5, $2;
    sltu  $2, $2, $4;
    bnez  $2, L00116E78;
    nop;
    bnez  $3, L00116E78;
    nop;
    sync;
    cache 0x14, 0x1($6);
    sync;
L00116E78:
    sync;
    addiu $6, $6, 0x40;
    slti  $2, $6, 0x1000;
    bnez  $2, L00116E00;
    nop;
    jr    $31;
    nop;
}
