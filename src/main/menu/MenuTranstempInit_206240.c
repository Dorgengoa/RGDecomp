#include "types.h"

extern void RecStackMemStackCreate_201d80(void *, void *, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C450[];
extern s32 D_00481BFC;
extern u8 D_004BBFE0[];

void MenuTranstempInit_206240(void)
{
    RecStackMemStackCreate_201d80(D_004BBFE0, &D_00481BFC, D_0045C450, 0xFA00);
}
