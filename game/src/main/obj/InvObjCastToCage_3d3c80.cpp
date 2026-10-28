/* rgp:protos */
#line 1
#include "types.h"

/* Ask the object whether it accepts mode 0x6; hand it back if it does.  The
   result is kept in the callee-saved register the `jalr` delay slot loads,
   so the null is written over it rather than branched around.

   Clone of EquipSlotDynamicCastKind2_39fe70: this group varies only in the mode constant and
   the vtable slot. */

class VA {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x20, a0, rgp_fwd2, rgp_fwd3); }
};

extern "C" VA *InvObjCastToCage_3d3c80(VA *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    return o->v6(0x6, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0 ? o : 0;
}
