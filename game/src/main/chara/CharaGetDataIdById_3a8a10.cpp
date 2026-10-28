#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
};

extern "C" s32 CharaMgrPoolFindById_3a8c60(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 CharaGetDataIdById_3a8a10(s32 p0, s32 p1)
{
    s32 r0;
    s32 r1;

    r0 = CharaMgrPoolFindById_3a8c60(p0, p1);
    if (r0 != 0) {
        r1 = ((struct C0 *)r0)->v21();
        return r1;
    }
    return -1;
}
