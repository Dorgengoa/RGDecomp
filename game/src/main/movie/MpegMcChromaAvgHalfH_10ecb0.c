#include "types.h"

/* Handwritten function (asm/matchings/main/MpegMcChromaAvgHalfH_10ecb0.s: "Handwritten
   function"). VU0-style packed-byte blend/averaging loop -- transcribed
   verbatim. */

void MpegMcChromaAvgHalfH_10ecb0(void *param_1)
{
    asm volatile {
        .set noreorder
        lw         $14, 0x0($4)
        lw         $5, 0x14($4)
        lw         $6, 0x18($4)
        lw         $3, 0x10($4)
        lw         $13, 0x4($4)
        pnor       $25, $0, $0
        psrlh      $25, $25, 15
        addiu      $24, $0, 0x1
        addiu      $12, $0, -0x1
        sll        $2, $3, 1
      outer:
        lw         $7, 0x8($4)
        addiu      $11, $0, -0x1
      inner:
        ld         $8, 0x0($5)
        ld         $9, 0x0($6)
        pcpyld     $8, $9, $8
        mtsab      $13, 0x0
        qfsrv      $8, $8, $8
        pextlb     $9, $0, $8
        addi       $7, $7, -0x1
        addu       $5, $5, $3
        addu       $6, $6, $3
        mtsab      $24, 0x0
        qfsrv      $10, $0, $8
        pextlb     $8, $0, $10
        paddh      $10, $9, $8
        paddh      $10, $10, $25
        psrlh      $10, $10, 1
        lq         $8, 0x0($14)
        paddh      $10, $10, $8
        pcgth      $9, $10, $0
        psrlh      $9, $9, 15
        paddh      $10, $10, $9
        psrlh      $10, $10, 1
        sq         $10, 0x0($14)
        bgtz       $7, inner
        addu       $14, $14, $2
        addiu      $5, $5, 0x140
        addiu      $6, $6, 0x140
        lw         $7, 0xC($4)
        and        $10, $11, $7
        bnez       $10, inner
        daddu      $11, $0, $0
        lw         $14, 0x0($4)
        lw         $5, 0x14($4)
        lw         $6, 0x18($4)
        addiu      $14, $14, 0x80
        addiu      $5, $5, 0x40
        addiu      $6, $6, 0x40
        bnez       $12, outer
        daddu      $12, $0, $0
    }
}
