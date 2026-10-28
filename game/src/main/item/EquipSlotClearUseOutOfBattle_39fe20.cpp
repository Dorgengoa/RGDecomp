/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    s32 v8(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x28, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483748;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x20];
    struct Obj1 *m20;
};

struct Obj1 {
    u8 pad000[0x24C];
    u8 m24C;
};

extern "C" s32 EquipSlotClearUseOutOfBattle_39fe20(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    struct Obj0 * t0;
    struct Obj1 * t1;
    u8 t2;
    s32 rv1;
    s32 r0;

    t0 = D_00483748;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_00483748->m20;
    t2 = D_00483748->m20->m24C;
    rv1 = 1;
    if ((t2 & 1) != 0) {
        rv1 = 0;
    } else {
        r0 = ((struct C0 *)p0)->v8((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
        rv1 = 1;
    }
    return rv1;
}
