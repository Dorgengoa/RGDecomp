/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    s32 v8() { return VCM0(s32, 0x28); }
};

extern "C" void UnitBaseResetIdsAndClear_3b8a60(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 UnitCtorReset_3b8a80(s32 p0)
{ s32 rgp_v0;
    UnitBaseResetIdsAndClear_3b8a60(p0);
    rgp_v0 = ((struct C0 *)p0)->v8();
return rgp_v0; }
