#include "types.h"

extern void RecStackMemStackCreate_201d80(void *, void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C4B0[];
extern s32 D_00481BE0;
extern u8 D_004BBDA0[];

void MenuSpaceStackInit_206570(void)
{
    RecStackMemStackCreate_201d80(D_004BBDA0, &D_00481BE0, D_0045C4B0, 0x8000);
}
