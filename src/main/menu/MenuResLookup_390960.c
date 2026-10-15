#include "types.h"

extern s32 GetMenuResGroup_206a40(void);
extern s32 ResGroupListFindValueById_42c3a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MenuResLookup_390960(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetMenuResGroup_206a40();
    if (r0 != 0) {
        r1 = ResGroupListFindValueById_42c3a0(r0, p0);
        return r1;
    }
    return 0;
}
