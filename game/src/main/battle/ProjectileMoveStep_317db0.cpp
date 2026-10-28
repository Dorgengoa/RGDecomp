/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

class V {
public:
    VC_VPTR_MEMBER; u8 * get() { return VCM0(u8 *, 0x8); }
};

extern "C" void VecAddScaled_13bdd0(u8 *, u8 *, f32);
extern "C" void JudgeObjectStep_314360(void *, int, float);

extern "C" u8 *ProjectileMoveStep_317db0(u8 *o, V *v, f32 f)
{
    u8 *r;

    JudgeObjectStep_314360((void *)o, (int)v, (float)f);
    if (!(*(f32 *)(o + 0xC8) < 0.0f)) {
        return 0;
    }
    *(f32 *)(o + 0x1B4) = *(f32 *)(o + 0x1B4) + *(f32 *)(o + 0x1C4) * f;
    *(u128 *)(o + 0x1A0) = *(u128 *)(o + 0x180);
    VecAddScaled_13bdd0(o + 0x180, o + 0x1B0, f);
    *(s32 *)(o + 0x1CC) = 0;
    if (v == 0) {
        return 0;
    }
    if (!(*(s32 *)(o + 0x7C) & 4)) {
        return 0;
    }
    r = v->get();
    *(u128 *)(r + 0x0) = *(u128 *)(o + 0x1A0);
    *(u128 *)(r + 0x10) = *(u128 *)(o + 0x180);
    *(f32 *)(r + 0x20) = *(f32 *)(o + 0x190);
    *(s32 *)(r + 0x24) = *(s32 *)(o + 0x7C);
    if (!(*(f32 *)(o + 0xCC) <= 0.0f)) {
        *(s32 *)(r + 0x24) &= ~8;
    }
    return r;
}
