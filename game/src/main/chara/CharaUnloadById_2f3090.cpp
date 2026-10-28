#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v171(s32 a0) { return VCM(s32, (void *, s32), 0x2B4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v268(s32 a0) { return VCM(s32, (void *, s32), 0x438, a0); }
};

extern "C" s32 GetActionMgr_1fdb50(void);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" s32 GetCharaResMgr_1fdb60(void);
extern "C" void ActionMgrRemoveChara_233dc0(s32, s32);
extern "C" void CharaResReleaseById_1f1160(s32, s32, s32);
extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ObjFindById_3bb3a0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    s32 m1C;
};

extern "C" void CharaUnloadById_2f3090(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;
    struct Obj0 *r5;
    s32 t0;
    s32 r6;

    r0 = GetActionMgr_1fdb50();
    r1 = GetCurrentScene_1f5be0();
    r2 = GetCharaResMgr_1fdb60();
    ActionMgrRemoveChara_233dc0(r0, p0);
    CharaResReleaseById_1f1160(r2, r1, p0);
    if (p1 != 0) {
        r5 = (struct Obj0 *)GetGameData_1fede0();
        t0 = r5->m1C;
        r6 = ObjFindById_3bb3a0(t0, p0);
        if (r6 != 0) {
            ((struct C0 *)r6)->v171(0);
            ((struct C0 *)r6)->v268(1);
        }
        return;
    }
}
