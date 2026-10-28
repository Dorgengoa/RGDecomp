#include "types.h"

/* Handwritten function (asm/matchings/main/MpegMcLumaAvgHalfHV_10ed80.s: "Handwritten
   function"). VU0-style packed-byte blend/averaging loop, sibling of
   MpegMcChromaAvgHalfH_10ecb0 -- transcribed verbatim. Trailing jr $31/nop OMITTED per
   the lever in MODEL.md: mwcc auto-appends it without a frame. */

void MpegMcLumaAvgHalfHV_10ed80(void *param_1)
{
    asm volatile {
        .set noreorder
        lw         $14, 0x0($4)
        lw         $5, 0x14($4)
        lw         $6, 0x18($4)
        lw         $24, 0x10($4)
        lw         $13, 0x4($4)
        lw         $7, 0x8($4)
        pnor       $25, $0, $0
        psrlh      $25, $25, 15
        psllh      $25, $25, 1
        addiu      $12, $0, 0x1
        lq         $8, 0x0($5)
        lq         $9, 0x0($6)
        mtsab      $13, 0x0
        qfsrv      $10, $9, $8
        qfsrv      $15, $8, $9
        pextlb     $8, $0, $10
        pextub     $9, $0, $10
        addiu      $11, $0, -0x1
        mtsab      $12, 0x0
        qfsrv      $15, $15, $10
        pextlb     $10, $0, $15
        pextub     $15, $0, $15
        paddh      $8, $8, $10
        beqz       $7, skip
        paddh      $9, $9, $15
      loop:
        addu       $5, $5, $24
        addu       $6, $6, $24
        lq         $10, 0x0($5)
        lq         $15, 0x0($6)
        mtsab      $13, 0x0
        qfsrv      $2, $15, $10
        qfsrv      $3, $10, $15
        pextlb     $10, $0, $2
        addi       $7, $7, -0x1
        pextub     $15, $0, $2
        mtsab      $12, 0x0
        qfsrv      $3, $3, $2
        pextlb     $2, $0, $3
        pextub     $3, $0, $3
        paddh      $10, $10, $2
        paddh      $15, $15, $3
        paddh      $2, $8, $10
        paddh      $3, $9, $15
        por        $8, $10, $0
        por        $9, $15, $0
        paddh      $2, $2, $25
        paddh      $3, $3, $25
        psrlh      $2, $2, 2
        psrlh      $3, $3, 2
        lq         $10, 0x0($14)
        lq         $15, 0x10($14)
        paddh      $2, $2, $10
        paddh      $3, $3, $15
        pnor       $25, $0, $0
        psrlh      $25, $25, 15
        paddh      $10, $2, $25
        psrlh      $2, $10, 1
        paddh      $10, $3, $25
        psrlh      $3, $10, 1
        sq         $2, 0x0($14)
        sll        $10, $24, 1
        sq         $3, 0x10($14)
        bgtz       $7, loop
        addu       $14, $14, $10
      skip:
        addiu      $5, $5, 0x80
        addiu      $6, $6, 0x80
        lw         $7, 0xC($4)
        and        $10, $11, $7
        bnez       $10, loop
        daddu      $11, $0, $0
    }
}
