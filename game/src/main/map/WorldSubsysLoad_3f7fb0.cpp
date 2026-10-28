#include "types.h"

/* Latch the pending value on the owner and notify BOTH listeners.  The
   second call reloads $5 because the first clobbered it; the first inherits
   the incoming argument untouched, which is why only one of the two call
   sites materialises it.

   Clone of WorldSubsysLoad_3f43b0: this group varies only in the two flag globals and
   the three field offsets. */

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    s32 v5(void * a0, s32 a1, s32 a2) { return VCM(s32, (void *, void *, s32, s32), 0x1C, a0, a1, a2); }
};

typedef struct Owner003f7fb0 {
    s32   m00;
    s32   m04;
    VB   *m08;
    VB   *m0C;
} Owner003f7fb0;

/* Wider than four bytes so mwcc gives these %hi/%lo instead of a $gp load. */
extern "C" struct rgp_anon_D_00465758 { s32 v; u8 pad[0xC]; } D_00465758;
extern "C" struct rgp_anon_D_00465760 { s32 v; u8 pad[0xC]; } D_00465760;

extern "C" s32 WorldSubsysLoad_3f7fb0(Owner003f7fb0 *o, void *p, s32 unused, s32 v)
{
    VB *l1;
    VB *l2;

    if (p == 0) {
        return 0;
    }
    if (o->m00 == 0) {
        return 0;
    }
    o->m04 = v;
    l1 = o->m08;
    if (l1 != 0) {
        l1->v5(p, D_00465758.v != 0, 0);
    }
    l2 = o->m0C;
    if (l2 != 0) {
        l2->v5(p, D_00465760.v != 0, 0);
    }
    return 1;
}
