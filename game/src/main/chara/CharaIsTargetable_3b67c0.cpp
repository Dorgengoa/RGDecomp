/* rgp:protos */
#line 1
#include "types.h"

/* Clone group w2b-007: `jalr $25` off the vptr at +0x00, slot 0xC0 =
   index (0xC0-8)/4 = 46.  The sltu/xori pair is a bool NEGATION of the
   s32 the virtual returned. */

class ObjFUN_003b67c0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 s046(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0xC0, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" u32 CharaIsTargetable_3b67c0(ObjFUN_003b67c0 *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    return (bool)(!self->s046((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3)));
}
