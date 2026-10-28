/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x004F7AF0 -- as 004F7A80 but the base-class tail runs too: two more
 * vptr writes at +0x1B0 and a member teardown at +0x1F0.
 * [[jalr-is-cpp-virtual]] */

class VS {
public:
    u8 pad000[0xE0];
    VC_VPTR_MEMBER; 
    void s02(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }               /* slot 0x10 */
};

struct RawObj {
    u8 pad000[0xF0];
    const void *volatile vptr0F0;
    u8 pad0F4[0x1B0 - 0xF4];
    const void *volatile vptr1B0;
};

extern "C" u8 D_0046FFA0[];
extern "C" u8 D_0046FFC0[];
extern "C" u8 D_00470440[];
extern "C" u8 D_0047D030[];
extern "C" void MotionListInit_1726f0(void *p);

extern "C" void *insect_ModelObjBaseCtor_4f7af0(void *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    ((RawObj *)o)->vptr1B0 = D_0046FFC0;
    ((RawObj *)o)->vptr0F0 = D_0046FFA0;
    ((VS *)((s32)o + 0x10))->s02((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    *(const void *volatile *)((s32)o + 0x1B0) = D_00470440;
    *(const void *volatile *)((s32)o + 0x1B0) = D_0047D030;
    MotionListInit_1726f0((void *)((s32)o + 0x1F0));
    return o;
}
