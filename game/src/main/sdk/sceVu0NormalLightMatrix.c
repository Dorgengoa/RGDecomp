#include "types.h"

extern void sceVu0ScaleVector(void);
extern void sceVu0Normalize(void); /* sceVu0Normalize, not yet promoted */
extern void sceVu0TransposeMatrix(void);

/* Naked `asm void` (lever 6): a plain-C wrapper compiled to sq/16-byte
   callee-saved slots here where retail uses sd/8-byte slots (the
   library-band compiler-identity wall). Transcribed by hand instead.
   l0 (arg2, $5) is never callee-saved -- it's consumed by the first
   ScaleVector call before anything else can clobber it. */

asm void sceVu0NormalLightMatrix(void)
{
    .set noreorder;
    addiu $29, $29, -0x60;
    swc1  $f20, 0x50($29);
    lui   $1, (0xBF800000 >> 16);
    mtc1  $1, $f20;
    sd    $16, 0x10($29);
    daddu $16, $4, $0;
    sd    $18, 0x30($29);
    sd    $17, 0x20($29);
    daddu $18, $7, $0;
    daddu $17, $6, $0;
    mov.s $f12, $f20;
    sd    $31, 0x40($29);
    jal   sceVu0ScaleVector;
    daddu $4, $29, $0;
    daddu $4, $16, $0;
    jal   sceVu0Normalize;
    daddu $5, $29, $0;
    daddu $5, $17, $0;
    mov.s $f12, $f20;
    jal   sceVu0ScaleVector;
    daddu $4, $29, $0;
    addiu $4, $16, 0x10;
    jal   sceVu0Normalize;
    daddu $5, $29, $0;
    daddu $5, $18, $0;
    mov.s $f12, $f20;
    jal   sceVu0ScaleVector;
    daddu $4, $29, $0;
    addiu $4, $16, 0x20;
    jal   sceVu0Normalize;
    daddu $5, $29, $0;
    mtc1  $0, $f0;
    daddu $4, $16, $0;
    lui   $1, (0x3F800000 >> 16);
    mtc1  $1, $f1;
    daddu $5, $4, $0;
    swc1  $f0, 0x30($16);
    swc1  $f1, 0x3C($16);
    swc1  $f0, 0x38($16);
    jal   sceVu0TransposeMatrix;
    swc1  $f0, 0x34($16);
    ld    $31, 0x40($29);
    ld    $18, 0x30($29);
    ld    $17, 0x20($29);
    ld    $16, 0x10($29);
    lwc1  $f20, 0x50($29);
    jr    $31;
    addiu $29, $29, 0x60;
}
