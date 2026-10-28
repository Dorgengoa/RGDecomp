#include "types.h"

/* Naked `asm void` transcription (scripts/naked_asm_gen.py). Session 43:
   the trailing `nop nop` pair is real content, not spimdisasm padding --
   see ThrowException_1025c0.c's note for the generator fix this needed. */

extern void iWakeupThread_117468(void);

asm void _request_call(void)
{
    .set noreorder;
    lw         $5, 0x34($4);
    lw         $6, 0x40($5);
    lw         $2, 0xC($6);
    bnel       $2, $0, L0011A474;
    lw        $2, 0x10($6);
    b          L0011A478;
    sw        $5, 0xC($6);
  L0011A474:
    sw         $5, 0x3C($2);
  L0011A478:
    sw         $5, 0x10($6);
    lw         $2, 0x14($4);
    lw         $3, 0x1C($4);
    sw         $2, 0x20($5);
    sw         $3, 0x1C($5);
    lw         $2, 0x20($4);
    sw         $2, 0x24($5);
    lw         $3, 0x24($4);
    sw         $3, 0xC($5);
    lw         $2, 0x28($4);
    sw         $2, 0x28($5);
    lw         $3, 0x2C($4);
    sw         $3, 0x2C($5);
    lw         $2, 0x30($4);
    sw         $2, 0x30($5);
    lw         $3, 0x10($4);
    sw         $3, 0x34($5);
    lw         $4, 0x0($6);
    bltz       $4, L0011A4DC;
    nop;
    lw         $2, 0x4($6);
    bnez       $2, L0011A4DC;
    nop;
    j          iWakeupThread_117468;
    nop;
  L0011A4DC:
    jr         $31;
    nop;
    nop;
}

