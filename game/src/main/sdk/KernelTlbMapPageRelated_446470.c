#include "types.h"

extern void func_075158(void);

/* Naked `asm void` (lever 6): TLB-related handwritten routine, calls a
   function outside the visible symbol table via a file-offset-derived
   name (`func_075158`, not a real vaddr-based name -- declared extern
   anyway since only the `jal` RELOCATION matters for the byte match, not
   whether the symbol resolves to anything real in this sandbox). Retail's
   `sd $31` sits in a `bnez`'s delay slot (interleaved prologue, same
   class lever 6 exists for). Ten trailing `nop`s past the registered
   size (0x130 = 76 words) are padding, not part of this unit. */

asm void KernelTlbMapPageRelated_446470(void)
{
    .set noreorder;
    addiu $29, $29, -0x30;
    sd    $16, 0x10($29);
    daddu $16, $4, $0;
    andi  $2, $16, 0xFFF;
    bnez  $2, L004464A0;
    sd    $31, 0x20($29);
    lui   $2, (0xFFFFE >> 16);
    addiu $3, $16, -0x1;
    ori   $2, $2, (0xFFFFE & 0xFFFF);
    sltu  $2, $2, $3;
    bnez  $2, L004464A8;
    lui   $4, (0x70004000 >> 16);
L004464A0:
    b     L00446590;
    addiu $2, $0, -0x1;
L004464A8:
    daddu $5, $29, $0;
    ori   $4, $4, (0x70004000 & 0xFFFF);
    ori   $6, $29, 0x4;
    jal   func_075158;
    ori   $7, $29, 0x8;
    daddu $5, $2, $0;
    bgez  $5, L004464E8;
    nop;
    beqz  $16, L00446590;
    daddu $2, $0, $0;
    mfc0  $5, $6;
    addiu $2, $5, 0x1;
    mtc0  $2, $6;
    sync.p;
    b     L00446530;
    nop;
L004464E8:
    bnez  $16, L00446530;
    addiu $2, $5, -0x1;
    lui   $3, (0xE0010000 >> 16);
    sll   $2, $2, 13;
    addu  $6, $2, $3;
    mfc0  $2, $6;
    addiu $2, $2, -0x1;
    mtc0  $2, $6;
    mtc0  $5, $0;
    mtc0  $0, $5;
    mtc0  $6, $10;
    mtc0  $0, $2;
    mtc0  $0, $3;
    sync.p;
    tlbwi;
    sync.p;
    b     L00446590;
    daddu $2, $0, $0;
L00446530:
    lui   $2, (0xFFFFF000 >> 16);
    addiu $4, $16, 0x1000;
    ori   $2, $2, (0xFFFFF000 & 0xFFFF);
    lui   $6, (0x70004000 >> 16);
    and   $4, $4, $2;
    sw    $0, 0x0($29);
    and   $2, $16, $2;
    srl   $4, $4, 6;
    srl   $2, $2, 6;
    ori   $4, $4, 0x1F;
    ori   $2, $2, 0x1F;
    ori   $6, $6, (0x70004000 & 0xFFFF);
    sw    $2, 0x4($29);
    sw    $4, 0x8($29);
    mtc0  $5, $0;
    daddu $3, $0, $0;
    mtc0  $3, $5;
    mtc0  $6, $10;
    mtc0  $2, $2;
    mtc0  $4, $3;
    sync.p;
    tlbwi;
    sync.p;
    daddu $2, $5, $0;
L00446590:
    ld    $31, 0x20($29);
    ld    $16, 0x10($29);
    jr    $31;
    addiu $29, $29, 0x30;
}
