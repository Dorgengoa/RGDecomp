/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v15(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x44, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    s32 v18() { return VCM0(s32, 0x50); }
};

extern "C" s32 EquipSlotGetGaugeMax_3a02d0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s16 m0C;
    u8 pad00E[0x2];
    f32 m10;
};

extern "C" s32 EquipSlotUseRefillGauge_3a0070(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s16 t0;
    s32 r1;
    s32 r2;

    r0 = ((struct C0 *)p0)->v15((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (r0 == 0) {
        return 0;
    }
    t0 = p0->m0C;
    p0->m0C = (t0 + 1);
    r1 = ((struct C0 *)p0)->v18();
    if (r1 != 0) {
        r2 = EquipSlotGetGaugeMax_3a02d0(p0);
        p0->m10 = ((f32)r2);
    }
    return 1;
}
