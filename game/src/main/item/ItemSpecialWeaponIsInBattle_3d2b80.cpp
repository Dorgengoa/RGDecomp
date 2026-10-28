/* rgp:protos */
#line 1
#include "types.h"

struct C0 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v47(s32 a0) { return VCM(s32, (void *, s32), 0xC4, a0); }
};

extern "C" s32 ItemWeaponIsInBattle_3d3180(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" s32 ItemSpecialWeaponIsInBattle_3d2b80(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((unsigned char)ItemWeaponIsInBattle_3d3180());
    if ((r0 & 0xFF) == 0) {
        return 0;
    }
    r1 = ((struct C0 *)p0)->v47(0);
    return 1;
}
