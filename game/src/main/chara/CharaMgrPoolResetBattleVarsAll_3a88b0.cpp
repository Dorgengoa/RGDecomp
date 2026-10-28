#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v47() { return VCM0(s32, 0xC4); }
};

extern "C" s32 PoolGetUsedElem_36acb0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004659B8;
extern "C" struct Obj0 * D_004837E8;

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
    u8 pad000[0x8];
    s32 m08;
};

extern "C" s32 CharaMgrPoolResetBattleVarsAll_3a88b0(struct Obj2 *p0)
{
    struct Obj0 * t0;
    struct Obj1 * t1;
    u8 t2;
    s32 rv5;
    s32 t3;
    s32 rv4;
    s32 t4;
    s32 l0;
    s32 t5;
    s32 r1;
    s32 rv3;
    s32 r2;

    t0 = D_004837E8;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_004837E8->m20;
    t2 = D_004837E8->m20->m24C;
    if ((t2 & 1) != 0) {
        rv5 = 0;
    } else {
        t3 = p0->m08;
        rv4 = 1;
        if (t3 == 0) {
            rv4 = 0;
        } else {
            t4 = D_004659B8;
            l0 = 0;
            while (l0 < t4) {
                t5 = p0->m08;
                r1 = PoolGetUsedElem_36acb0(t5, l0);
                rv3 = r1;
                if (r1 != 0) {
                    r2 = ((struct C0 *)r1)->v47();
                    rv3 = r2;
                }
                l0 = (l0 + 1);
            }
            rv4 = 1;
        }
        rv5 = rv4;
    }
    return rv5;
}
