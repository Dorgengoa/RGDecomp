/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

class Obj30 {
    u8 pad[0x30];
public:
    VC_VPTR_MEMBER;
    void v0C() { VCM0(void, 0xC); }
    s32 v10(u128 * a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, u128 *, int, int), 0x10, a0, rgp_fwd2, rgp_fwd3); }
};

class ObjE0 {
    u8 pad[0xE0];
public:
    VC_VPTR_MEMBER;
    s32 v0C(s32 a0) { return VCM(s32, (void *, s32), 0xC, a0); }
};

extern "C" void AabbTransformBounds_13c710(u128 *arg0, u128 *arg1, void *arg2, u128 *arg3, u128 *arg4);
extern "C" void BoundsFrom4Points_13df00(u128 *arg0, u128 *arg1, u128 *arg2, u128 *arg3, u128 *arg4, u128 *arg5);
extern "C" void FrameCalcWorldMatrix_148ff0(void *arg0, void *arg1);

extern "C" s32 CollFrameTreeCalcBounds_16be80(void *arg0, u128 *arg1, int rgp_a2, int rgp_a3)
{
    u128 spC0;
    u128 spB0;
    u8 sp70[0x40] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(u128)) + (0x10 + sizeof(u128)) + (0x20) + (0x10)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(u128) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    s32 var_19;
    ObjE0 *var_18;
    Obj30 *temp_4;
    ObjE0 *var_17;
    

    var_19 = 0;
    temp_4 = *(Obj30 **)((u8 *)arg0 + 0xF4);
    if (temp_4 != NULL && temp_4->v10(&spB0, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) != 0) {
        FrameCalcWorldMatrix_148ff0(arg0, sp70);
        var_19 = 1;
        AabbTransformBounds_13c710(&spB0, &spC0, sp70, &spB0, &spC0);
    }
    var_18 = *(ObjE0 **)((u8 *)arg0 + 0x8);
    while (var_18 != NULL) {
        var_17 = 0;
        if (var_18->v0C(0x2714) != 0) {
            var_17 = var_18;
        }
        if ((var_17 != NULL) && (CollFrameTreeCalcBounds_16be80(var_17, &(*(u128 *)(rgp_blk1 + 0x0)), 0, 0) != 0)) {
            if (var_19 == 0) {
                spB0 = (*(u128 *)(rgp_blk1 + 0x0));
                spC0 = (*(u128 *)(rgp_blk1 + 0x10));
            } else {
                BoundsFrom4Points_13df00(&spB0, &spC0, &spB0, &spC0, &(*(u128 *)(rgp_blk1 + 0x0)), &(*(u128 *)(rgp_blk1 + 0x10)));
            }
            var_19 = 1;
        }
        var_18 = *(ObjE0 **)((u8 *)var_18 + 0xC);
    }
    arg1[0] = spB0;
    arg1[1] = spC0;
    return var_19;
}
