#include "types.h"

extern void sceVu0RotMatrixZ(void);
extern void sceVu0RotMatrixY(void);
extern void sceVu0RotMatrixX(void);

/* Naked `asm void` (lever 6): a plain-C wrapper compiled to sq/16-byte
   callee-saved slots here where retail uses sd/8-byte slots (the
   library-band compiler-identity wall). Transcribed by hand instead;
   third call is a real tail `j`. */

asm void sceVu0RotMatrix(void)
{
    .set noreorder;
    addiu $29, $29, -0x30;
    sd    $17, 0x10($29);
    sd    $16, 0x0($29);
    daddu $17, $6, $0;
    sd    $31, 0x20($29);
    daddu $16, $4, $0;
    jal   sceVu0RotMatrixZ;
    lwc1  $f12, 0x8($17);
    lwc1  $f12, 0x4($17);
    daddu $4, $16, $0;
    jal   sceVu0RotMatrixY;
    daddu $5, $16, $0;
    daddu $4, $16, $0;
    lwc1  $f12, 0x0($17);
    ld    $31, 0x20($29);
    daddu $5, $4, $0;
    ld    $17, 0x10($29);
    ld    $16, 0x0($29);
    j     sceVu0RotMatrixX;
    addiu $29, $29, 0x30;
}
