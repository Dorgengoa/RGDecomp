#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

struct C400 {
    u8 pad000[0x190];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v16(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x48, a0, a1, a2); }
};

extern "C" s32 ScriptSlotGetInt_3348b0(E8 *);
extern "C" s32 GetEffectMgr_2d9040(void);
extern "C" void ScriptSlotStoreIntRef_3347f0(E8 *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004826E0;

extern "C" s32 ScriptCmdEffectElemAlloc_331960(E8 *p0, s32 p1)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 t1;
    s32 r2;

    r0 = ScriptSlotGetInt_3348b0(p0++);
    t0 = D_004826E0;
    if (t0 == 0) {
        return 0;
    }
    r1 = GetEffectMgr_2d9040();
    t1 = D_004826E0;
    r2 = ((struct C400 *)t1)->v16(0, (s16)r0, r1);
    if (p1 == 2) {
        ScriptSlotStoreIntRef_3347f0(p0, r2);
    }
    return 1;
}
