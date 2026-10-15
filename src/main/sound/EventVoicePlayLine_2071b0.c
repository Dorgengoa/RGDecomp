#include "types.h"

extern s32 GetStreamMgr_207ea0(void);
extern void StreamMgrPauseChan_1d6630(s32, s32);
extern void StreamMgrStopChan_1d66b0(s32, s32);
extern void Sprintf_1343b8(void *, void *, s32, s32, s32, s32, s32);
extern void PathLocalize_1c28c0(void *, void *);
extern void StreamMgrStartChan_1d66f0(s32, s32, void *, s32);
extern void StreamMgrPlayChan_1d6670(s32, s32, f32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C570[];

void EventVoicePlayLine_2071b0(s32 p0, s32 p1, s32 p2, f32 fa0)
{
    u128 vE0[8];
    u128 v60[8];
    s32 r0;

    r0 = GetStreamMgr_207ea0();
    StreamMgrPauseChan_1d6630(r0, 1);
    StreamMgrStopChan_1d66b0(r0, 1);
    if (p0 >= 0) {
        if (p1 >= 0) {
            if (p2 >= 0) {
                Sprintf_1343b8(vE0, D_0045C570, p0, p1, p0, p1, p2);
                PathLocalize_1c28c0(v60, vE0);
                StreamMgrStartChan_1d66f0(r0, 1, v60, 0);
                StreamMgrPlayChan_1d6670(r0, 1, fa0);
            }
        }
    }
}
