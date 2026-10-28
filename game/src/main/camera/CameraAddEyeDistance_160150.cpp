/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v27(f32 a0) { return VCM(s32, (void *, f32), 0x74, a0); }
    f32 v28() { return VCM0(f32, 0x78); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CameraAddEyeDistance_160150(s32 p0, f32 fa0)
{ s32 rgp_v0;
    f32 r0;

    r0 = ((struct C192 *)p0)->v28();
    rgp_v0 = ((struct C192 *)p0)->v27((fa0 + r0));
return rgp_v0; }
