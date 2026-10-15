#include "types.h"
#pragma opt_common_subs off

extern void VecNormalize_13bd90(void *, void *);
extern void VecScale_13be00(void *, void *, f32);
extern void VecAdd_13be20(void *, void *, void *);
extern void VecSub_13be40(void *, void *, void *);
extern void ModelSetPos_151110(s32, void *);
extern s32 ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 D_00481F78;

s32 EventCameraCmdPlaceObjOnView_254cf0(void *arg0, void *arg1) {
    u8 sp50[0x10];
    u8 sp40[0x10];
    void *p;
    s32 temp_2;
    s32 temp_3;

    temp_3 = *(s32 *)((u8 *)arg0 + 0x38);
    if ((temp_3 >= 0) && (*(s32 *)((u8 *)arg1 + 0x48) >= temp_3)) {
        *(s32 *)((u8 *)arg1 + 0x48) = 0;
        return 0;
    }
    temp_2 = ObjRecGetLiveObject_1c4a90(D_00481F78, *(s32 *)((u8 *)arg0 + 0x30));
    if (temp_2 == 0) {
        return 0;
    }
    VecSub_13be40(sp50, (u8 *)arg1 + 0x60, (u8 *)arg1 + 0x50);
    p = sp50;
    VecNormalize_13bd90(p, p);
    p = sp50;
    VecScale_13be00(p, p, *(f32 *)((u8 *)arg0 + 0x34));
    VecAdd_13be20(sp40, (u8 *)arg1 + 0x50, sp50);
    ModelSetPos_151110(temp_2, sp40);
    *(s32 *)((u8 *)arg1 + 0x48) = *(s32 *)((u8 *)arg1 + 0x48) + 1;
    return 1;
    return 0;
}
