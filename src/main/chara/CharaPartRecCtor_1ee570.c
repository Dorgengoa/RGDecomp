#include "types.h"

extern void ListNodeInit_1efa20(s32);
extern void MemStackCtor_14e030(s32);
extern s32 CharaDataSubRecInit_1eeab0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 CharaPartRecCtor_1ee570(s32 p0)
{
    s32 r2;

    ListNodeInit_1efa20(p0);
    MemStackCtor_14e030((p0 + 0xC));
    r2 = CharaDataSubRecInit_1eeab0(p0);
    return p0;
}
