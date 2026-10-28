/* rgp:protos */
#line 1
#include "types.h"
class C00186a20 {
public:
    u8 pad0[0x1B0];
    VC_VPTR_MEMBER;
    
    f32 v10(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(f32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad1b4[0x1C0 - 0x1B4];
    s32 unk1C0;
    u8 pad1c4[0x1C8 - 0x1C4];
    s32 unk1C8;
    s32 unk1CC;
    u8 pad1d0[0x1D4 - 0x1D0];
    f32 unk1D4;
    f32 unk1D8;
    s32 unk1DC;
    f32 unk1E0;
};

extern "C" s32 ModelObjIsVisible_186a20(C00186a20 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    f32 f;
    s32 r;

    f = o->v10((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (o->unk1C0 == 0) {
        return 0;
    }
    if (o->unk1DC != 0) {
        if (o->unk1E0 != 0.0f) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        r = o->unk1C8 == 0;
        if (!r) {
            r = 0;
        } else {
        if (o->unk1CC == 0) {
            r = 1;
        } else if (!(o->unk1D4 <= 0.0f) && !(f <= o->unk1D4)) {
            r = 0;
        } else if (!(o->unk1D8 <= 0.0f) && f < o->unk1D8) {
            r = 0;
        } else {
            r = 1;
        }
            if (r == 0) {
                r = 0;
            } else {
                r = 1;
            }
        }
    }
    return r;
}
