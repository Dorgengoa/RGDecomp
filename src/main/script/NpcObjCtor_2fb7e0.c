#include "types.h"

extern void HeadLookInit_1c5c50(s32);
extern s32 NpcObjInit_2fcd50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NpcObjCtor_2fb7e0(s32 p0)
{
    s32 r1;

    HeadLookInit_1c5c50((p0 + 0x10));
    r1 = NpcObjInit_2fcd50(p0);
    return p0;
}
