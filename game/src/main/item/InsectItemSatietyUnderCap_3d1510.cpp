/* rgp:protos */
#line 1
#include "types.h"

/* jalr through vtable slot 0x164: virtual_index = (0x164 - 8) / 4 = 87.
 * [[jalr-is-cpp-virtual]] */

class VE {
public:
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
    s32 v87(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x164, rgp_fwd1, rgp_fwd2, rgp_fwd3); }          /* slot 0x164 */
};

extern "C" s32 D_00465D80;
extern "C" f32 D_0047D440;

extern "C" s32 InsectItemSatietyUnderCap_3d1510(VE *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    f32 v;
    s32 result;

    v = (f32)self->v87((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    result = 1;
    if (!(v <= (D_0047D440 * (f32)(s32)(f32)D_00465D80))) {
        result = 0;
    }
    return result;
}
