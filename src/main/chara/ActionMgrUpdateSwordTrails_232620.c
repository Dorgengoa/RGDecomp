#include "types.h"

extern s32 DListGetHead_42ea60(s32);
extern void CharaSwordTrailsUpdate_214aa0(s32);
extern s32 DListGetNext_42eb30(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ActionMgrUpdateSwordTrails_232620(s32 p0)
{
    s32 r0;
    s32 l1;
    s32 r3;

    r0 = DListGetHead_42ea60((p0 + 0x20));
    l1 = r0;
    while (l1 != 0) {
        CharaSwordTrailsUpdate_214aa0((l1 + 0x10));
        r3 = DListGetNext_42eb30(l1);
        l1 = r3;
    }
}
