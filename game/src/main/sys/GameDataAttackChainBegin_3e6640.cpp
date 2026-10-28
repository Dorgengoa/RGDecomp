#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v318(s32 a0) { return VCM(s32, (void *, s32), 0x500, a0); }
};

extern "C" s32 CharaSysAttackChainBegin_3a10c0(s32);
extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);
extern "C" void ObjMgrAttackChainBegin_3ba610(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
    u8 pad018[0x4];
    s32 m1C;
    s32 m20;
};

extern "C" s32 GameDataAttackChainBegin_3e6640(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;
    s32 rv3;
    s32 t2;
    s32 t3;

    t0 = p0->m20;
    if (t0 != 0) {
        r0 = CharaSysAttackChainBegin_3a10c0(t0);
    }
    t1 = p0->m14;
    r1 = CharaMgrPoolFindById_3a8c60(t1, p1);
    if (r1 != 0) {
        ((struct C0 *)r1)->v318(p1);
    }
    ObjMgrAttackChainBegin_3ba610(p0->m1C, p1);
    return 1;
}
