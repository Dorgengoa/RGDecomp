/* rgp:protos */
#line 1
#pragma optimization_level 3
/* PARK s16d: 1 round trip, length 0x16C vs retail 0x15C (4 words over). */
#include "types.h"
extern "C" {
#pragma opt_common_subs off
#pragma opt_propagation off

extern void MtxIdentity_13d2e0(void *);
extern void ModelFrameSetMatrix_14a190(void *, void *);
extern s32 CollFrameTreeCollectTris_16bfb0(void *, s32, s32, s32, s32);
extern void NodeCalcWorldMatrix_186130(void *, void *);
class VD {
public:
    u8 pad[0xE0];
    VC_VPTR_MEMBER;
    s32 f(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0xC, a0, rgp_fwd2, rgp_fwd3); }
};


s32 NodeObjBasicCollectTrisWorld_196d70(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 arg_h4;

    s32 arg_h1;

    u8 spA0[0x40] __attribute__((aligned(16)));
    u8 sp60[0x40] __attribute__((aligned(16)));
    s32 flags;
    s32 mode;
    s32 one;
    s32 result;
    void *p70;
    void *vtbl;

    flags = *(s32 *)((u8 *)arg0 + 0x78);
    if (!(flags & 1)) {
        return 0;
    }
    mode = 0;
    if (flags & 8) {
        one = 1;
        if (arg1 == one) {
            mode = one;
        }
        if (arg1 == 3) {
            mode = 2;
        }
    } else if (arg1 == flags) {
        mode = 3;
    }
    if (mode == 0) {
        return 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0x32) == 0) {
        return 0;
    }
    p70 = *(void **)((u8 *)arg0 + 0x70);
    if (p70 == NULL) {
        return 0;
    }
    if (((VD *)p70)->f(0x2714, (int)(long)(arg2), (int)(long)(arg3)) == 0) {
        return 0;
    }
    if (*(void **)((u8 *)arg0 + 0x70) != NULL) {
        NodeCalcWorldMatrix_186130(arg0, spA0);
        ModelFrameSetMatrix_14a190(*(void **)((u8 *)arg0 + 0x70), spA0);
    }
    arg_h1 = mode;
    arg_h4 = arg4;
    result = CollFrameTreeCollectTris_16bfb0(*(void **)((u8 *)arg0 + 0x70), arg_h1, arg2, arg3, arg_h4);
    if (*(void **)((u8 *)arg0 + 0x70) != NULL) {
        MtxIdentity_13d2e0(sp60);
        ModelFrameSetMatrix_14a190(*(void **)((u8 *)arg0 + 0x70), sp60);
        p70 = *(void **)((u8 *)arg0 + 0x70);
        if (*(s8*)((u8 *)p70 + 0x28) != 0) {
            *(s32 *)((u8 *)p70 + 0x4) = 0;
        }
    }
    return result;
}

}
