/* rgp:protos */
#line 1
#include "types.h"

extern "C" struct rgp_anon_D_00465D78 { s32 v; s32 pad[3]; } D_00465D78;

/* jalr $25 x3 -- C++ virtual member calls. Slot offset = 8 + 4*N.
   0x1A4 -> N=103 (no explicit arg), 0x1B4 -> N=107 (explicit arg=this),
   0x1AC -> N=105 (explicit arg=this). Dummy virtuals declared-never-
   defined so no vtable/undefined-symbol noise. */

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v103(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x1A4, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    s32 v105() { return VCM0(s32, 0x1AC); }
    
    s32 v107() { return VCM0(s32, 0x1B4); }
};

extern "C" s32 InsectItemIsMaxLevel_3d1570(VE *obj, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 temp_16;
    s32 temp_16_2;

    temp_16 = D_00465D78.v;
    if (temp_16 == obj->v103((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3))) {
        temp_16_2 = obj->v107();
        if (temp_16_2 >= obj->v105()) {
            return 1;
        }
    }
    return 0;
}
