/* rgp:protos */
#line 1
#include "types.h"

/* clone group cg06-000 -- exemplar StateBlockDeserialize_3cb970, MATCHED.
   Two guards are ONE || (separate ifs put the shared return-0 block in the
   wrong place); the range extern must be an ARRAY or mwcc puts it in sdata and
   emits gp-relative instead of hi/lo; and "total = 0;" sits BETWEEN the ||
   guard and the range guard -- that is what fills the third branch's delay
   slot and leaves the jalr slot a nop.  Vtable slot read off each member's own
   listing. */

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    s32 slot1C(void *p, s32 n, int rgp_fwd3 = 0) { return VCM(s32, (void *, void *, s32, int), 0x1C, p, n, rgp_fwd3); }
};

extern "C" s32 D_004658F8[4];

extern "C" s32 InsectTeamTableDeserialize_42fd70(Obj *self, void *p, s32 n, int rgp_a3)
{
    s32 total;

    if (p == 0 || n <= 0) return 0;
    total = 0;
    if (D_004658F8[0] < n) return 0;
    total += self->slot1C(p, n, (int)(long)(rgp_a3));
    return total;
}
