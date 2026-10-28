#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v102(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x1A0, a0, a1, a2); }
};

extern "C" s32 ScriptGetInt_26a2a0(s32);
extern "C" void * GetGameData_1fede0(void);
extern "C" s32 ObjFindById_3bb3a0(s32, s32);
extern "C" s32 GetEventObjMgr_2d1960(void);
extern "C" s32 EvRemoveChrMonographs_2e9060(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1C];
    s32 m1C;
};

extern "C" s32 EvCmdObjDisableMaybe_269580(s32 p0, s32 p1)
{
    s32 r0;
    struct Obj0 *r1;
    s32 t0;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 rv6;
    s32 r5;

    if (p1 <= 0) {
        return 1;
    }
    r0 = ScriptGetInt_26a2a0(p0);
    r1 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r1->m1C;
    r2 = ObjFindById_3bb3a0(t0, r0);
    if (r2 != 0) {
        r3 = ((struct C0 *)r2)->v102(0x1F, 0, 1);
        r4 = GetEventObjMgr_2d1960();
        rv6 = 0;
        if (r4 != 0) {
            r5 = EvRemoveChrMonographs_2e9060(r4, r0);
            rv6 = r5;
        }
    }
    return 1;
}
