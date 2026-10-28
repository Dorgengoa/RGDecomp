#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v103(s32 a0) { return VCM(s32, (void *, s32), 0x1A4, a0); }
};

extern "C" s32 EventObjMgrGetTypeList_2e9d60(s32, s32);
extern "C" s32 DListGetHead_42ea60(s32);
extern "C" void ObjTypeMonographMarkRemoveIfTargetKind5_372810(s32, s32);
extern "C" s32 DListGetNext_42eb30(s32);
extern "C" s32 GetGameData_1fede0(void);
extern "C" s32 ActorFindById_3eb870(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 EvRemoveChrMonographs_2e9060(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r4;
    s32 r5;
    s32 r6;

    r0 = EventObjMgrGetTypeList_2e9d60(p0, 5);
    r1 = DListGetHead_42ea60(r0);
    l2 = r1;
    while (l2 != 0) {
        ObjTypeMonographMarkRemoveIfTargetKind5_372810((l2 + 0x10), p1);
        r4 = DListGetNext_42eb30(l2);
        l2 = r4;
    }
    r5 = GetGameData_1fede0();
    r6 = ActorFindById_3eb870(r5, p1);
    if (r6 != 0) {
        ((struct C0 *)r6)->v103(0x1F);
    }
}
