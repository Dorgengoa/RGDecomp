#include "types.h"

/* Handwritten function (asm/matchings/main/MpegMcChromaAvgHalfHV_10eea0.s: "Handwritten
   function"). VU0-style packed-byte blend/averaging loop family, sibling of
   MpegMcChromaAvgHalfH_10ecb0/MpegMcLumaAvgHalfHV_10ed80 -- transcribed verbatim. Trailing jr $31/nop
   OMITTED per the lever in MODEL.md. Retail carries one extra trailing nop
   after its own jr/nop (alignment padding) -- left for db.sh to reveal
   whether mwcc's auto epilogue reproduces it or it needs to be added back. */

void MpegMcChromaAvgHalfHV_10eea0(void *param_1)
{
    asm volatile {
        .set noreorder
        lw         $14, 0x0($4)
        lw         $5, 0x14($4)
        lw         $6, 0x18($4)
        lw         $12, 0x10($4)
        lw         $13, 0x4($4)
        pnor       $25, $0, $0
        psrlh      $25, $25, 15
        psllh      $25, $25, 1
        addiu      $24, $0, 0x1
        addiu      $11, $0, 0x1
      outer:
        lw         $7, 0x8($4)
        ld         $8, 0x0($5)
        ld         $9, 0x0($6)
        pcpyld     $8, $9, $8
        mtsab      $13, 0x0
        qfsrv      $8, $8, $8
        pextlb     $9, $0, $8
        addu       $5, $5, $12
        ori        $11, $11, 0x8000
        mtsab      $24, 0x0
        qfsrv      $10, $0, $8
        pextlb     $8, $0, $10
        beqz       $7, tail1
        paddh      $15, $9, $8
      loop:
        addu       $6, $6, $12
        ld         $8, 0x0($5)
        ld         $9, 0x0($6)
        pcpyld     $8, $9, $8
        mtsab      $13, 0x0
        qfsrv      $8, $8, $8
        pextlb     $9, $0, $8
        addi       $7, $7, -0x1
        addu       $5, $5, $12
        mtsab      $24, 0x0
        qfsrv      $10, $0, $8
        pextlb     $8, $0, $10
        paddh      $10, $9, $8
        paddh      $9, $10, $15
        por        $15, $10, $0
        paddh      $10, $9, $25
        psrlh      $10, $10, 2
        lq         $8, 0x0($14)
        paddh      $10, $10, $8
        pcgth      $9, $10, $0
        psrlh      $9, $9, 15
        paddh      $10, $10, $9
        sll        $8, $12, 1
        psrlh      $10, $10, 1
        sq         $10, 0x0($14)
        bgtz       $7, loop
        addu       $14, $14, $8
      tail1:
        psrah      $10, $11, 15
        addiu      $5, $5, 0x140
        lw         $7, 0xC($4)
        addiu      $6, $6, 0x140
        and        $10, $10, $7
        bnez       $10, loop
        andi       $11, $11, 0x7FFF
        lw         $14, 0x0($4)
        lw         $5, 0x14($4)
        lw         $6, 0x18($4)
        addiu      $14, $14, 0x80
        addiu      $5, $5, 0x40
        addiu      $6, $6, 0x40
        andi       $10, $11, 0x1
        bnez       $10, outer
        andi       $11, $11, 0xFFFE
    }
}
