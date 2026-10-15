#include "types.h"

extern void EvFollowObjReset_2f8170(s32);
extern void EvObjInitByName_2f9de0(s32, s32, s32, s32);
extern void TargetRefSetMapObj_2e6470(s32, s32, s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvFollowObjInitByName_2f80e0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    EvFollowObjReset_2f8170(p0);
    EvObjInitByName_2f9de0(p0, p1, p2, p3);
    TargetRefSetMapObj_2e6470((p0 + 0xA0), p4, p5, 0.0f);
}
