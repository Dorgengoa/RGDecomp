#include "types.h"

extern void MsgTableLookup_28aa30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004831E0;

void SaveMenuMsgLookup_376b30(s32 p0)
{
    s32 t0;

    t0 = D_004831E0;
    MsgTableLookup_28aa30(t0, p0);
}
