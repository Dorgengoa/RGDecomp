/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20() { return VCM0(s32, 0x58); }
    s32 v21(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x5C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void CameraChaseStep_161b60(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" void CameraModeSetupTrack_309000(s32 p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 r0;
    s32 r1;

    r0 = ((struct C192 *)p0)->v21((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    r1 = ((struct C192 *)p0)->v20();
    CameraChaseStep_161b60(p0, 1.0f);
}
