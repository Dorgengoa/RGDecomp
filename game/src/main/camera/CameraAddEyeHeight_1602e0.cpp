/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v24(f32 a0) { return VCM(s32, (void *, f32), 0x68, a0); }
    
    f32 v26() { return VCM0(f32, 0x70); }
};



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CameraAddEyeHeight_1602e0(s32 p0, f32 fa0)
{ s32 rgp_v0;
    f32 r0;

    r0 = ((struct C192 *)p0)->v26();
    rgp_v0 = ((struct C192 *)p0)->v24((fa0 + r0));
return rgp_v0; }
