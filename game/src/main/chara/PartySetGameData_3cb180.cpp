/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    s32 v5(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x1C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" struct Obj0 * D_00483890;
extern "C" s32 D_00483894;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

extern "C" s32 PartySetGameData_3cb180(s32 p0, struct Obj0 *p1, int rgp_a2, int rgp_a3)
{
    s32 t0;
    s32 r0;

    if (p1 == 0) {
        return 0;
    }
    D_00483890 = p1;
    t0 = p1->m08;
    D_00483894 = t0;
    r0 = ((struct C0 *)p0)->v5((int)(long)(p1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    return 1;
}
