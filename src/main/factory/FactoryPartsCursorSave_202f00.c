#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00481BA0;
extern u8 D_00481BA1;

void FactoryPartsCursorSave_202f00(s32 p0, s32 p1)
{
    D_00481BA0 = p0;
    D_00481BA1 = p1;
}
