#include "types.h"

extern s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern s32 DListGetHead_42ea60(s32);
extern s32 EvMapObjSetReverseRateFromFrames_366970(s32, s32, s32);
extern s32 DListGetNext_42eb30(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EventObjMgrMapObjsSetReverseRateFromFrames_2e9490(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r3;
    s32 r4;

    r0 = EventObjMgrGetTypeList_2e9d60(p0, 8);
    r1 = DListGetHead_42ea60(r0);
    l2 = r1;
    while (l2 != 0) {
        r3 = EvMapObjSetReverseRateFromFrames_366970((l2 + 0x10), p1, p2);
        r4 = DListGetNext_42eb30(l2);
        l2 = r4;
    }
}
