#include "types.h"

/* D-cache writeback loop (registered name sceSifWriteBackDCache, stale
   lane-file name FUN_00119ab0). Naked `asm void`, no callee-saved regs,
   no calls -- would also work as a plain `asm volatile` leaf but written
   this way for consistency with the rest of the vein. */

asm void sceSifWriteBackDCache(void)
{
    .set noreorder;
    lui   $25, (0xFFFFFFC0 >> 16);
    ori   $25, $25, (0xFFFFFFC0 & 0xFFFF);
    blez  $5, L00119B54;
    addu  $10, $4, $5;
    and   $8, $4, $25;
    addiu $10, $10, -0x1;
    and   $9, $10, $25;
    subu  $10, $9, $8;
    srl   $11, $10, 6;
    addiu $11, $11, 0x1;
    andi  $9, $11, 0x7;
    beqz  $9, L00119B00;
    srl   $10, $11, 3;
L00119AE4:
    sync;
    cache 0x18, 0x0($8);
    sync;
    nop;
    addiu $9, $9, -0x1;
    bgtz  $9, L00119AE4;
    addiu $8, $8, 0x40;
L00119B00:
    beqz  $10, L00119B54;
L00119B04:
    addiu $10, $10, -0x1;
    sync;
    cache 0x18, 0x0($8);
    sync;
    cache 0x18, 0x40($8);
    sync;
    cache 0x18, 0x80($8);
    sync;
    cache 0x18, 0xC0($8);
    sync;
    cache 0x18, 0x100($8);
    sync;
    cache 0x18, 0x140($8);
    sync;
    cache 0x18, 0x180($8);
    sync;
    cache 0x18, 0x1C0($8);
    sync;
    bgtz  $10, L00119B04;
    addiu $8, $8, 0x200;
L00119B54:
    jr    $31;
    nop;
}
