/* rgp:protos */
#line 1
#include "types.h"

/* retail's arg0->unk50->unkC(arg0, 2) call goes through `jalr $25` -- only a
   real C++ virtual dispatch reaches that (jalr-is-cpp-virtual lever). The
   vptr sits at +0x50 (padding before the first virtual), `this` stays the
   outer pointer (arg0 itself, unmodified before the call). slot 0xC => 1
   dummy virtual ahead of the real one (slot = 8 + 4*N). */
class VE0014e430 {
public:
    u8 pad000[0x50];
    VC_VPTR_MEMBER;
    s32 v1(s32 arg1, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0xC, arg1, rgp_fwd2, rgp_fwd3); }
    u8 pad054[0x64 - 0x54];
    s32 unk64;                          /* 0x64 */
    u8 pad068[0x128 - 0x68];
    s32 unk128;                         /* 0x128 */
    s32 unk12C;                         /* 0x12C */
};

extern "C" s32 ModelMeshGetVuVariantFlagsMaybe_14e430(VE0014e430 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 ret;
    s32 cond;

    ret = 0;
    if (arg0->v1(2, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        cond = arg0->unk128 > 0;
        if (cond != 0) {
            cond = arg0->unk12C != 0;
        }
        if (cond & 0xFF) {
            ret |= 1;
        }
        cond = arg0->unk64 != 0x20;
        if (cond & 0xFF) {
            ret |= 2;
        }
    }
    return ret;
}
