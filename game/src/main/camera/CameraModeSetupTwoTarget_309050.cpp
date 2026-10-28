/* rgp:protos */
#line 1
#include "types.h"

struct C192 {
    u8 pad000[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v20() { return VCM0(s32, 0x58); }
};

extern "C" void CameraSetControlFlagsMaybe_161d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 D_00482940;
extern "C" s32 D_00482944;

extern "C" s32 CameraModeSetupTwoTarget_309050(s32 p0)
{ s32 rgp_v0;
    D_00482940 = 0;
    D_00482944 = 0;
    CameraSetControlFlagsMaybe_161d40(p0, 1);
    rgp_v0 = ((struct C192 *)p0)->v20();
return rgp_v0; }
