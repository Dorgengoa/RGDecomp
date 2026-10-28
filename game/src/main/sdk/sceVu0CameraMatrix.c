#include "types.h"

extern void sceVu0UnitMatrix(void);
extern void sceVu0OuterProduct(void); /* sceVu0OuterProduct, not yet promoted */
extern void sceVu0Normalize(void); /* sceVu0Normalize, not yet promoted */
extern void sceVu0TransMatrix(void);
extern void sceVu0InversMatrix(void);

/* Naked `asm void` (lever 6): a plain-C wrapper compiled to sq/16-byte
   callee-saved slots here where retail uses sd/8-byte slots (the
   library-band compiler-identity wall). Transcribed by hand instead.
   Builds a camera basis at $sp+0x0 (Mtx4) / $sp+0x40 (Vec4 xd), then
   inverts it into the caller's matrix. */

asm void sceVu0CameraMatrix(void)
{
    .set noreorder;
    addiu $29, $29, -0xB0;
    sd    $20, 0x90($29);
    daddu $20, $4, $0;
    sd    $19, 0x80($29);
    sd    $18, 0x70($29);
    daddu $19, $5, $0;
    sd    $17, 0x60($29);
    daddu $18, $6, $0;
    daddu $17, $7, $0;
    sd    $16, 0x50($29);
    sd    $31, 0xA0($29);
    jal   sceVu0UnitMatrix;
    daddu $4, $29, $0;
    addiu $16, $29, 0x40;
    daddu $5, $17, $0;
    daddu $4, $16, $0;
    jal   sceVu0OuterProduct;
    daddu $6, $18, $0;
    daddu $5, $16, $0;
    jal   sceVu0Normalize;
    daddu $4, $29, $0;
    addiu $16, $29, 0x20;
    daddu $5, $18, $0;
    jal   sceVu0Normalize;
    daddu $4, $16, $0;
    daddu $5, $16, $0;
    addiu $4, $29, 0x10;
    jal   sceVu0OuterProduct;
    daddu $6, $29, $0;
    daddu $6, $19, $0;
    daddu $4, $29, $0;
    jal   sceVu0TransMatrix;
    daddu $5, $29, $0;
    daddu $4, $20, $0;
    jal   sceVu0InversMatrix;
    daddu $5, $29, $0;
    ld    $31, 0xA0($29);
    ld    $20, 0x90($29);
    ld    $19, 0x80($29);
    ld    $18, 0x70($29);
    ld    $17, 0x60($29);
    ld    $16, 0x50($29);
    jr    $31;
    addiu $29, $29, 0xB0;
}
