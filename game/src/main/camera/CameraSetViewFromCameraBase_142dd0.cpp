/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    s32 v7(void * a0) { return VCM(s32, (void *, void *), 0x24, a0); }
    
    
    
    
    
    s32 v13(void * a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, void *, int, int), 0x3C, a0, rgp_fwd2, rgp_fwd3); }
};

extern "C" void CameraSetView_156200(s32, void *, void *);
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xF20];
    s32 mF20;
};

extern "C" void CameraSetViewFromCameraBase_142dd0(struct Obj0 *p0, s32 p1, int rgp_a2, int rgp_a3)
{
    u128 v40[4];
    u128 v30;
    s32 t0;

    ((struct C192 *)p1)->v13(v40, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    ((struct C192 *)p1)->v7(&v30);
    t0 = p0->mF20;
    if (t0 != 0) {
        CameraSetView_156200(t0, v40, &v30);
        return;
    }
}
