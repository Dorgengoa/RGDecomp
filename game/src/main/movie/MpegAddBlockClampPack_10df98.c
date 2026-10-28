#include "types.h"

/* Hand-written: clamp+pack loop (paddh/pminh/pmaxh/ppacb), 8 rows unrolled
   per iteration. Loads a clamp-constant from a fixed address inside a
   NEIGHBOURING function's body (`MpegClampPackBlock_10e088 + 0xA8`) via lui/addiu --
   spelled as the literal resolved hi/lo (lever 5: `0x11` / `-0x1ED0`,
   since (0x11<<16)+(-0x1ED0) == 0x10E130 == 0x10E088+0xA8), no symbol
   needed. */

void MpegAddBlockClampPack_10df98(void)
{
    asm volatile {
        .set noreorder
        addiu $2, $0, 0x18
        lui   $10, 0x11
        addiu $10, $10, -0x1ED0
        lq    $3, 0x0($10)
    L0010DFA8:
        lq    $8, 0x0($6)
        addi  $2, $2, -0x4
        lq    $9, 0x10($6)
        lq    $10, 0x20($6)
        lq    $11, 0x30($6)
        lq    $12, 0x40($6)
        lq    $13, 0x50($6)
        lq    $14, 0x60($6)
        lq    $15, 0x70($6)
        lq    $25, 0x0($5)
        paddh $8, $8, $25
        lq    $25, 0x10($5)
        pminh $8, $8, $3
        pmaxh $8, $8, $0
        paddh $9, $9, $25
        lq    $25, 0x20($5)
        pminh $9, $9, $3
        pmaxh $9, $9, $0
        ppacb $9, $9, $8
        paddh $10, $10, $25
        pminh $10, $10, $3
        lq    $25, 0x30($5)
        pmaxh $10, $10, $0
        paddh $11, $11, $25
        lq    $25, 0x40($5)
        pminh $11, $11, $3
        pmaxh $11, $11, $0
        ppacb $11, $11, $10
        paddh $12, $12, $25
        lq    $25, 0x50($5)
        pminh $12, $12, $3
        pmaxh $12, $12, $0
        paddh $13, $13, $25
        lq    $25, 0x60($5)
        pminh $13, $13, $3
        pmaxh $13, $13, $0
        ppacb $13, $13, $12
        paddh $14, $14, $25
        lq    $25, 0x70($5)
        pminh $14, $14, $3
        pmaxh $14, $14, $0
        sq    $9, 0x0($4)
        paddh $15, $15, $25
        pminh $15, $15, $3
        pmaxh $15, $15, $0
        ppacb $15, $15, $14
        sq    $11, 0x10($4)
        sq    $13, 0x20($4)
        sq    $15, 0x30($4)
        addiu $5, $5, 0x80
        addiu $4, $4, 0x40
        bnez  $2, L0010DFA8
        addiu $6, $6, 0x80
    }
}
