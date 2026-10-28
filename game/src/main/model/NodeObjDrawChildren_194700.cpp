#include "types.h"

class VE {
    u8 pad_[0x68];
public:
    VC_VPTR_MEMBER;
    f32 f0C() { return VCM0(f32, 0xC); }
};

/* $f21 is the scale, $f20 the saved per-node value; both are callee-saved FPRs
   so they are named locals.  Fall-through of the beql is the `!= 0` arm, so the
   AND-mask is the `if` body and the OR is the `else`.
   Indirect call: table pointer at 0x68 of the owner, slot 0xC. */


extern "C" void GetDrawCtx_15de80(void);
extern "C" s32 InRangeWrap_1922b0(f32, f32, f32);
extern "C" s32 NodeObjBasicDrawFromParentMaybe_196a00(void *);

extern "C" s32 NodeObjDrawChildren_194700(u8 *self)
{
    s32 total;
    u8 *it;
    u8 *o;
    f32 scale;
    f32 saved;

    GetDrawCtx_15de80();
    scale = *(f32 *)(self + 0x64);
    if (*(s32 *)(self + 0x50) != 0) {
        scale = scale * ((VE *)self)->f0C();
    }
    it = *(u8 **)(self + 0x94);
    total = 0;
    while (it != 0) {
        o = *(u8 **)(it + 0x10);
        if (InRangeWrap_1922b0(*(f32 *)(self + 0x148), *(f32 *)(o + 0x84),
                         *(f32 *)(o + 0x88)) != 0) {
            *(s32 *)(o + 0x3C) = *(s32 *)(o + 0x3C) & 0xBFFFFFFF;
        } else {
            *(s32 *)(o + 0x3C) = *(s32 *)(o + 0x3C) | 0x40000000;
        }
        saved = *(f32 *)(o + 0x64);
        *(u8 **)(o + 0x34) = self;
        *(s32 *)(o + 0x38) = 0;
        *(f32 *)(o + 0x64) = saved * scale;
        total += NodeObjBasicDrawFromParentMaybe_196a00(o);
        *(s32 *)(o + 0x34) = 0;
        *(s32 *)(o + 0x38) = 0;
        *(f32 *)(o + 0x64) = saved;
        it = *(u8 **)(it + 0x00);
    }
    return total;
}
