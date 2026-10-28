#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v106() { return VCM0(s32, 0x1B0); }
};

extern "C" s32 PoolGetUsedElem_36acb0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_004659B8;
extern "C" s32 D_004837E8;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

extern "C" s32 CharaMgrPoolStatusFxStopAll_3a85f0(struct Obj0 *p0)
{
    s32 t0;
    s32 t1;
    s32 rv4;
    s32 t2;
    s32 l0;
    s32 t3;
    s32 r1;
    s32 rv3;
    s32 r2;

    t0 = D_004837E8;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m08;
    rv4 = 1;
    if (t1 == 0) {
        rv4 = 0;
    } else {
        t2 = D_004659B8;
        l0 = 0;
        while (l0 < t2) {
            t3 = p0->m08;
            r1 = PoolGetUsedElem_36acb0(t3, l0);
            rv3 = r1;
            if (r1 != 0) {
                r2 = ((struct C0 *)r1)->v106();
                rv3 = r2;
            }
            l0 = (l0 + 1);
        }
        rv4 = 1;
    }
    return rv4;
}
