#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 v10() { return VCM0(s32, 0x30); }
};

extern "C" s32 GameRecMarkInsectSlotReclaimable_3ce300(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj1 * D_004838F0;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x14];
    s16 m14;
};

struct Obj1 {
    u8 pad000[0x174];
    s32 m174;
};

extern "C" s32 ItemGameRecMarkReclaimable_3d2520(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 t2;
    s32 r0;
    s32 r1;

    t0 = D_004838F0;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m14;
    t2 = D_004838F0->m174;
    r0 = GameRecMarkInsectSlotReclaimable_3ce300(t2, t1);
    r1 = ((struct C0 *)p0)->v10();
    return 1;
}
