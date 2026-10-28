#include "types.h"

/* Naked `asm void` transcription (scripts/naked_asm_gen.py). Session 43:
   the trailing `nop` past the `jr $31` delay slot is real content, not
   spimdisasm padding -- see ThrowException_1025c0.c's note for the generator fix
   this needed. Also note: this function's own `sd $16/$17/$31` callee-saves
   are the library-band "different toolchain" marker ([[main-library-band]])
   when a real C recompile is asked to reproduce them, but that only bites C
   -- literal transcription bypasses the compiler's save-width decision
   entirely, so it's not a wall for the naked-asm lever specifically. */

extern void scePadGetDmaStr(void);

asm void scePadInfoComb(void)
{
    .set noreorder;
    daddu      $8, $4, $0;
    addiu      $3, $0, 0x70;
    addiu      $4, $0, 0x1C;
    mult1      $3, $8, $3;
    mult       $4, $5, $4;
    addiu      $29, $29, -0xB0;
    lui        $2, 0x49;
    sd         $17, 0x90($29);
    sd         $16, 0x80($29);
    addiu      $2, $2, -0x12B0;
    sd         $31, 0xA0($29);
    daddu      $17, $6, $0;
    addu       $4, $4, $3;
    addu       $2, $2, $4;
    lw         $3, 0x10($2);
    beqz       $3, L0012BC84;
    daddu     $16, $7, $0;
    daddu      $4, $8, $0;
    jal        scePadGetDmaStr;
    daddu     $6, $29, $0;
    lbu        $3, 0x72($29);
    addiu      $2, $0, 0x1;
    bne        $3, $2, L0012BC88;
    daddu     $2, $0, $0;
    lbu        $2, 0x64($29);
    sltiu      $2, $2, 0x2;
    bnez       $2, L0012BC88;
    daddu     $2, $0, $0;
    addiu      $4, $0, -0x1;
    bne        $17, $4, L0012BC0C;
    lbu       $2, 0x6B($29);
    b          L0012BC8C;
    ld        $31, 0xA0($29);
  L0012BC0C:
    slt        $2, $17, $2;
    beql       $2, $0, L0012BC88;
    daddu     $2, $0, $0;
    beql       $16, $0, L0012BC60;
    sll       $2, $17, 2;
    bgtz       $16, L0012BC38;
    nop;
    beq        $16, $4, L0012BC54;
    sll       $2, $17, 2;
    b          L0012BC88;
    daddu     $2, $0, $0;
  L0012BC38:
    beq        $16, $3, L0012BC6C;
    sll       $2, $17, 2;
    addiu      $2, $0, 0x2;
    beq        $16, $2, L0012BC78;
    sll       $2, $17, 2;
    b          L0012BC88;
    daddu     $2, $0, $0;
  L0012BC54:
    addu       $3, $29, $2;
    b          L0012BC88;
    lbu       $2, 0x40($3);
  L0012BC60:
    addu       $3, $29, $2;
    b          L0012BC88;
    lbu       $2, 0x41($3);
  L0012BC6C:
    addu       $3, $29, $2;
    b          L0012BC88;
    lbu       $2, 0x42($3);
  L0012BC78:
    addu       $3, $29, $2;
    b          L0012BC88;
    lbu       $2, 0x43($3);
  L0012BC84:
    daddu      $2, $0, $0;
  L0012BC88:
    ld         $31, 0xA0($29);
  L0012BC8C:
    ld         $17, 0x90($29);
    ld         $16, 0x80($29);
    jr         $31;
    addiu     $29, $29, 0xB0;
    nop;
}

