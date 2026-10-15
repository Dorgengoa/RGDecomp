#include "types.h"

extern void MemStackCtor_14e030(void *);
extern void TextStyleInit_26c610(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E7B40[];
extern u8 D_004E7BA0[];

void StaticInitSysFont_46cb90(void)
{
    MemStackCtor_14e030(D_004E7B40);
    TextStyleInit_26c610(D_004E7BA0);
}
