#include "types.h"

/* Handwritten function (asm/matchings/main/MpegToIpuDmaHandler_112a48.s: "Handwritten
   function"). SIF DMA-chain kick variant, sibling of MpegCscDmaHandler_112900 --
   transcribed verbatim. Retail tail is `jr $31; daddu $2,$0,$0; nop` -- an
   extra pad word past the delay slot, which mwcc's auto-appended return
   cannot reproduce (BRIEF's "resists" shape) when using `asm volatile{}`
   with the jr omitted. Fully NAKED `asm void` sidesteps that: every `$31`
   operand (including the mid-block early return) can be spelled directly,
   and the final `jr $31` + its real delay-slot instruction + the extra
   trailing `nop` are all just emitted verbatim, no auto-anything. */

asm void MpegToIpuDmaHandler_112a48(void)
{
    .set noreorder;
    lui        $2, (0x1000E010 >> 16);
    addiu      $3, $0, 0x10;
    ori        $2, $2, (0x1000E010 & 0xFFFF);
    daddu      $6, $5, $0;
    sw         $3, 0x0($2);
    lw         $2, 0x0($6);
    bnez       $2, L00112A78;
    ori        $7, $0, 0xFFFF;
    sync;
    ei;
    jr         $31;
    addiu      $2, $0, 0x1;
L00112A78:
    sltu       $2, $7, $2;
    beqz       $2, L00112ADC;
    lui        $3, (0x1000B420 >> 16);
    lw         $4, 0x4($6);
    lui        $2, (0x1000B410 >> 16);
    ori        $2, $2, (0x1000B410 & 0xFFFF);
    sw         $4, 0x0($2);
    ori        $3, $3, (0x1000B420 & 0xFFFF);
    sw         $7, 0x0($3);
    lui        $2, (0x1000B400 >> 16);
    ori        $2, $2, (0x1000B400 & 0xFFFF);
    addiu      $3, $0, 0x101;
    sw         $3, 0x0($2);
    lui        $5, (0xFFFF0 >> 16);
    ori        $5, $5, (0xFFFF0 & 0xFFFF);
    lui        $4, (0xFFFFFFF >> 16);
    lw         $3, 0x4($6);
    ori        $4, $4, (0xFFFFFFF & 0xFFFF);
    lw         $2, 0x0($6);
    addu       $3, $3, $5;
    and        $3, $3, $4;
    subu       $2, $2, $7;
    sw         $2, 0x0($6);
    b          L00112B0C;
    sw         $3, 0x4($6);
L00112ADC:
    lw         $4, 0x4($6);
    lui        $2, (0x1000B410 >> 16);
    ori        $2, $2, (0x1000B410 & 0xFFFF);
    sw         $4, 0x0($2);
    ori        $3, $3, (0x1000B420 & 0xFFFF);
    lui        $2, (0x1000B400 >> 16);
    addiu      $5, $0, 0x101;
    lw         $4, 0x0($6);
    ori        $2, $2, (0x1000B400 & 0xFFFF);
    sw         $4, 0x0($3);
    sw         $5, 0x0($2);
    sw         $0, 0x0($6);
L00112B0C:
    sync;
    ei;
    jr         $31;
    daddu      $2, $0, $0;
    nop;
}
