#include "types.h"

extern void EventVoiceChanStop_24e9e0(void *, s32, s32, s32);
extern s32 MesWinCalcTextWaitFrames_24e2f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
    s32 m10;
};

void EventVoiceStopSetWait_24e8c0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 t0;
    s32 r1;

    EventVoiceChanStop_24e9e0(p0, p1, p2, p3);
    if (p3 <= 0) {
        t0 = p0->m0C;
        r1 = MesWinCalcTextWaitFrames_24e2f0(t0);
        p0->m10 = r1;
        return;
    }
}
