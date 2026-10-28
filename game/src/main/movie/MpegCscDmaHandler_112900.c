#include "types.h"

/* Handwritten function (asm/matchings/main/MpegCscDmaHandler_112900.s: "Handwritten
   function"). SIF DMA-chain kick with interrupt masking -- transcribed
   verbatim. Two early "jr $31" returns kept explicit (real early exits);
   the FINAL jr $31/delay-slot pair had its `jr $31` dropped per the lever
   in MODEL.md (mwcc auto-appends its own, no frame), keeping the delay
   slot's `daddu $2,$0,$0` as the block's last line. */

void MpegCscDmaHandler_112900(void *param_1, void *param_2)
{
    asm volatile {
        .set noreorder
        lui        $2, (0x1000E010 >> 16)
        addiu      $3, $0, 0x8
        ori        $2, $2, (0x1000E010 & 0xFFFF)
        daddu      $9, $5, $0
        sw         $3, 0x0($2)
        lui        $4, (0x1000B020 >> 16)
        ori        $4, $4, (0x1000B020 & 0xFFFF)
        lw         $2, 0x0($9)
        addiu      $2, $2, 0x1
        sw         $2, 0x0($9)
        lw         $3, 0x0($4)
        bnez       $3, l_294c
        addiu      $2, $0, 0x1
        lui        $2, (0x1000B000 >> 16)
        ori        $2, $2, (0x1000B000 & 0xFFFF)
        lw         $3, 0x0($2)
        andi       $3, $3, 0x100
        beqz       $3, l_2960
        addiu      $2, $0, 0x1
      l_294c:
        sw         $2, 0x4($9)
        sync
        ei
        .word      0x03e00008 /* jr $31 -- .word, not the mnemonic: an
                                  explicit `jr $31` mnemonic ANYWHERE in an
                                  asm volatile block makes mwcc insert its
                                  own ABI frame (measured); .word with the
                                  identical encoding does not, since mwcc's
                                  own scan for an explicit return never sees
                                  it as a jr. See MODEL.md. */
        daddu      $2, $0, $0
      l_2960:
        lw         $3, 0x10($9)
        lw         $2, 0x0($9)
        addiu      $3, $3, -0x1
        slt        $2, $2, $3
        beqz       $2, l_29d4
        lui        $2, (0x1000B010 >> 16)
        lw         $3, 0xC($9)
        ori        $2, $2, (0x1000B010 & 0xFFFF)
        ori        $4, $0, 0xFFC0
        sw         $3, 0x0($2)
        addiu      $5, $0, 0x100
        lui        $1, (0x10010000 >> 16)
        sw         $4, -0x4FE0($1)
        lui        $3, (0x10002000 >> 16)
        lui        $2, (0x700003FF >> 16)
        lui        $1, (0x10010000 >> 16)
        sw         $5, -0x5000($1)
        ori        $3, $3, (0x10002000 & 0xFFFF)
        ori        $2, $2, (0x700003FF & 0xFFFF)
        sw         $2, 0x0($3)
        lui        $4, (0xFFC00 >> 16)
        ori        $4, $4, (0xFFC00 & 0xFFFF)
        lui        $3, (0xFFFFFFF >> 16)
        lw         $2, 0xC($9)
        ori        $3, $3, (0xFFFFFFF & 0xFFFF)
        addu       $2, $2, $4
        and        $2, $2, $3
        b          l_2a38
        sw         $2, 0xC($9)
      l_29d4:
        lw         $2, 0x0($9)
        bne        $2, $3, l_2a38
        addiu      $8, $0, 0x100
        lw         $5, 0x0($9)
        lui        $4, (0x1000B010 >> 16)
        lw         $3, 0x8($9)
        ori        $4, $4, (0x1000B010 & 0xFFFF)
        sll        $2, $5, 10
        lw         $6, 0xC($9)
        subu       $2, $2, $5
        subu       $3, $3, $2
        lui        $5, (0x10002000 >> 16)
        sw         $3, 0x8($9)
        lui        $7, (0x70000000 >> 16)
        sw         $6, 0x0($4)
        ori        $5, $5, (0x10002000 & 0xFFFF)
        lw         $2, 0x8($9)
        sll        $2, $2, 6
        lui        $1, (0x10010000 >> 16)
        sw         $2, -0x4FE0($1)
        lui        $1, (0x10010000 >> 16)
        sw         $8, -0x5000($1)
        lw         $2, 0x8($9)
        or         $2, $2, $7
        sw         $2, 0x0($5)
      l_2a38:
        sync
        ei
        daddu      $2, $0, $0
    }
}
