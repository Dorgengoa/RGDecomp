#include "types.h"

extern void sceVu0CopyVector(void); /* sceVu0CopyVector, not yet promoted */

/* Naked `asm void` (lever 6): a plain-C wrapper compiled to sq/16-byte
   callee-saved slots here where retail uses sd/8-byte slots (the
   library-band compiler-identity wall). Transcribed by hand instead.
   c0 (arg2, $5) is never callee-saved -- consumed by the first CopyVector
   call before anything else can clobber it. Fourth call is a real tail `j`.
   NOTE: `a` (5th arg) arrives in $8, not on the stack -- unexplained ABI
   quirk, transcribed as retail has it rather than guessed at. */

asm void sceVu0LightColorMatrix(void)
{
    .set noreorder;
    addiu $29, $29, -0x50;
    sd    $16, 0x0($29);
    daddu $16, $4, $0;
    sd    $19, 0x30($29);
    sd    $18, 0x20($29);
    daddu $19, $8, $0;
    sd    $17, 0x10($29);
    daddu $18, $7, $0;
    sd    $31, 0x40($29);
    jal   sceVu0CopyVector;
    daddu $17, $6, $0;
    daddu $5, $17, $0;
    jal   sceVu0CopyVector;
    addiu $4, $16, 0x10;
    daddu $5, $18, $0;
    jal   sceVu0CopyVector;
    addiu $4, $16, 0x20;
    addiu $4, $16, 0x30;
    daddu $5, $19, $0;
    ld    $31, 0x40($29);
    ld    $19, 0x30($29);
    ld    $18, 0x20($29);
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    j     sceVu0CopyVector;
    addiu $29, $29, 0x50;
}
