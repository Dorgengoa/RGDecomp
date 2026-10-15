#include "types.h"

extern void TextStyleInit_26c610(s32);
extern s32 MesWinInit_276f20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MesWinCtor_276ef0(s32 p0)
{
    s32 r1;

    TextStyleInit_26c610(p0);
    r1 = MesWinInit_276f20(p0);
    return p0;
}
