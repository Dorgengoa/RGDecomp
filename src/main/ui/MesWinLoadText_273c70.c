#include "types.h"

extern void MesWinClearChars_2744b0(s32);
extern void MesWinSetFlush_2775f0(s32, s32);
extern void MesWinLayoutText_274e70(s32, s32);
extern void MesWinPushChar_2743c0(s32, s32);
extern void MesWinCountPageLines_2726d0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinLoadText_273c70(s32 p0, s32 p1, s32 p2)
{
    if (p1 != 0) {
        MesWinClearChars_2744b0(p0);
        MesWinSetFlush_2775f0(p0, 0);
        MesWinLayoutText_274e70(p0, p1);
        if (p2 != 0) {
            MesWinPushChar_2743c0(p0, 0xFF01);
        }
        MesWinCountPageLines_2726d0(p0);
    }
}
