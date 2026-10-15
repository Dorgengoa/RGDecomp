#include "types.h"

extern s32 MsgGetActiveTable_2790a0(void);
extern s32 MsgTableLookup_28aa30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0044EC20[];

s32 MsgGetTextByIndex_279040(s32 p0)
{
    s32 t0;
    s32 r0;
    s32 r1;

    if (p0 < 0 || p0 >= 0x32) {
        return 0;
    }
    t0 = *(s32 *)((u8 *)D_0044EC20 + (p0 << 2));
    r0 = MsgGetActiveTable_2790a0();
    r1 = MsgTableLookup_28aa30(r0, t0);
    return r1;
}
