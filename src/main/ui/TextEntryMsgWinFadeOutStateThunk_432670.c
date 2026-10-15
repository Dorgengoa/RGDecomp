#include "types.h"

extern void TextEntryMsgWinFadeOutState_432b10(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00484104;

s32 TextEntryMsgWinFadeOutStateThunk_432670(s32 p0, s32 p1)
{
    s32 t0;

    t0 = D_00484104;
    if (t0 != 0) {
        TextEntryMsgWinFadeOutState_432b10(t0, p1);
    }
    return 1;
}
