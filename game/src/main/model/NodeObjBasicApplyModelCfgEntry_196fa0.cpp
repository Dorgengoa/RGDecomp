/* rgp:protos */
#line 1
#include "types.h"

class VE {
    u8 pad_[0xE0];
public:
    VC_VPTR_MEMBER;
    s32 f0C(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0xC, a0, rgp_fwd2, rgp_fwd3); }
};

/* The two float tests branch in OPPOSITE directions -> an `||` whose then-arm
   is the shared block.  The second test reads through a sub-object pointer at
   +0x3C (offset 0x10 there == 0x4C), the first reads the just-stored 0x48
   through the object base.  Indirect call: table pointer at 0xE0, slot 0xC. */


extern "C" s32 NodeObjBasicApplyModelCfgEntry_196fa0(u8 *self, u8 *src, int rgp_a2, int rgp_a3)
{
    void *obj;
    s32 v;
    u8 *s;

    if (src == 0) {
        return 0;
    }
    *(s32 *)(self + 0x74) = *(s32 *)(src + 0x00);
    *(s32 *)(self + 0x78) = *(s32 *)(src + 0x04);
    v = *(s32 *)(src + 0x08);
    if (v != 0) {
        *(s32 *)(self + 0x6C) = v;
    }
    obj = *(void **)(src + 0x0C);
    if (obj != 0 && ((VE *)obj)->f0C(0x2714, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        *(void **)(self + 0x70) = obj;
    }
    *(f32 *)(self + 0x48) = *(f32 *)(src + 0x14);
    *(f32 *)(self + 0x4C) = *(f32 *)(src + 0x18);
    *(s32 *)(self + 0x50) = *(s32 *)(src + 0x1C);
    s = self + 0x3C;
    if (!(*(f32 *)(self + 0x48) <= 0.0f) || !(*(f32 *)(s + 0x10) <= 0.0f)) {
        *(s32 *)(s + 0x04) = 1;
        *(f32 *)(s + 0x1C) = *(f32 *)(src + 0x20);
        *(f32 *)(s + 0x20) = *(f32 *)(src + 0x24);
    }
    return 1;
}
