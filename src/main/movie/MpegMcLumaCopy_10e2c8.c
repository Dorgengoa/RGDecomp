#include "types.h"

/* UNREGISTERED symbol (no entry in config/main.symbols.txt at this vaddr
   under ANY name) -- db.sh cannot score this (see MODEL.md park note).
   Drafted anyway, ready to score the moment it's registered. Same
   func_0010Exxx byte-shuffle family as the eight already-matched
   siblings; final trailing `nop` dropped per the family's established
   lever-4 pattern (one dead word past the real end in every sibling
   checked so far -- unverified here since size is unknown, but assumed
   consistent; re-check against the registered size once it exists). */

asm void MpegMcLumaCopy_10e2c8(void)
{
    .set noreorder;
    lw    $14, 0x0($4);
    lw    $5, 0x14($4);
    lw    $6, 0x18($4);
    lw    $12, 0x10($4);
    lw    $8, 0x4($4);
    lw    $7, 0x8($4);
    mtsab $8, 0x0;
    sll   $11, $12, 1;
    addiu $15, $0, -0x1;
L0010E2EC:
    lq    $8, 0x0($5);
    lq    $9, 0x0($6);
    addi  $7, $7, -0x1;
    addu  $5, $5, $12;
    addu  $6, $6, $12;
    qfsrv $10, $9, $8;
    pextlb $8, $0, $10;
    pextub $9, $0, $10;
    sq    $8, 0x0($14);
    sq    $9, 0x10($14);
    bgtz  $7, L0010E2EC;
    addu  $14, $14, $11;
    addiu $5, $5, 0x80;
    addiu $6, $6, 0x80;
    lw    $7, 0xC($4);
    and   $10, $15, $7;
    bnez  $10, L0010E2EC;
    daddu $15, $0, $0;
    jr    $31;
    nop;
    nop;
}
