#include "types.h"

typedef unsigned __int128 u128;

class Obj30 {
    u8 pad[0x30];
public:
    virtual void v08();
    virtual void v0C();
    virtual s32 v10(u128 *);
};

class ObjE0 {
    u8 pad[0xE0];
public:
    virtual void v08();
    virtual s32 v0C(s32);
};

extern "C" void AabbTransformBounds_13c710(u128 *arg0, u128 *arg1, void *arg2, u128 *arg3, u128 *arg4);
extern "C" void BoundsFrom4Points_13df00(u128 *arg0, u128 *arg1, u128 *arg2, u128 *arg3, u128 *arg4, u128 *arg5);
extern "C" void FrameCalcWorldMatrix_148ff0(void *arg0, void *arg1);

extern "C" s32 CollFrameTreeCalcBounds_16be80(void *arg0, u128 *arg1)
{
    u128 spC0;
    u128 spB0;
    u8 sp70[0x40];
    u128 sp60;
    s32 var_19;
    ObjE0 *var_18;
    Obj30 *temp_4;
    ObjE0 *var_17;
    u128 sp50;

    var_19 = 0;
    temp_4 = *(Obj30 **)((u8 *)arg0 + 0xF4);
    if (temp_4 != NULL && temp_4->v10(&spB0) != 0) {
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
        if ((var_17 != NULL) && (CollFrameTreeCalcBounds_16be80(var_17, &sp50) != 0)) {
            if (var_19 == 0) {
                spB0 = sp50;
                spC0 = sp60;
            } else {
                BoundsFrom4Points_13df00(&spB0, &spC0, &spB0, &spC0, &sp50, &sp60);
            }
            var_19 = 1;
        }
        var_18 = *(ObjE0 **)((u8 *)var_18 + 0xC);
    }
    arg1[0] = spB0;
    arg1[1] = spC0;
    return var_19;
}
