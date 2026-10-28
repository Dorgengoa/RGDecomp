#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v104(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v170(s32 a0, s32 a1, s32 a2) { return VCM(s32, (void *, s32, s32, s32), 0x2B0, a0, a1, a2); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483818;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x20];
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x24C];
    u8 m24C;
};

struct Obj2 {
    u8 pad000[0x408];
    u8 m408;
};

extern "C" s32 UnitOnBattleEnd_3bcec0(struct Obj2 *p0, s32 p1)
{
    struct Obj0 * t0;
    s32 r0;
    struct Obj0 * t1;
    struct Obj1 * t2;
    u8 t3;
    s32 rv3;
    u8 t4;
    s32 r1;
    s32 r2;

    t0 = D_00483818;
    if (t0 == 0) {
        return 0;
    }
    r0 = ((struct C0 *)p0)->v104(1, 1, 1);
    t1 = D_00483818;
    t2 = D_00483818->m20;
    t3 = D_00483818->m20->m24C;
    rv3 = 1;
    if ((t3 & 1) == 0) {
        rv3 = 0;
    } else {
        t4 = p0->m408;
        if ((((u64)(((s64)t4) << 0x38)) >> 0x3F) != 0) {
            r1 = ((struct C0 *)p0)->v170(0, 0, 1);
        }
        if (p1 == 3) {
            r2 = ((struct C0 *)p0)->v170(0, 0, 1);
        }
        rv3 = 1;
    }
    return rv3;
}
