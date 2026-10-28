/* rgp:protos */
#line 1
#include "types.h"

/* jalr through vtable slot 0x1C: virtual_index = (0x1C - 8) / 4 = 5.
 * [[jalr-is-cpp-virtual]] */

class VE {
public:
    VC_VPTR_MEMBER;  
     
    s32 v5(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x1C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }          /* slot 0x1C */
};

extern "C" s32 D_004658F8;
extern "C" void CharaSysEncounterResetMaybe_3a5b10(VE *arg0, s32 arg1, s32 arg2, s32 arg3);

extern "C" s32 CharaSysDeserialize_3a0ab0(VE *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    s32 temp_16;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    temp_16 = 0;
    if (D_004658F8 < arg2) {
        return 0;
    }
    temp_16 += arg0->v5((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3));
    CharaSysEncounterResetMaybe_3a5b10(arg0, 1, 1, 1);
    return temp_16;
}
