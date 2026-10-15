#include "types.h"

extern void MotionListUpdateAll_171e40(void *, f32);
extern void ClothSimStep_185170(s32);
extern void ModelObjApplyMotionList_186700(s32);

void MapAreaModelUpdateMotionCloth_187550(void *arg0, f32 fparg0) {
    u8 *var_16;
    u8 *var_17;
    s32 temp_16;
    s32 temp_4;

    var_17 = *(u8 **)((u8 *)arg0 + 0x2A0);
    while (var_17 != NULL) {
        temp_16 = *(s32 *)(var_17 + 0x10);
        if (temp_16 != 0) {
            MotionListUpdateAll_171e40((u8 *)temp_16 + 0x1F0, fparg0);
            ModelObjApplyMotionList_186700(temp_16);
        }
        var_17 = *(u8 **)var_17;
    }
    var_16 = *(u8 **)((u8 *)arg0 + 0x2A4);
    while (var_16 != NULL) {
        temp_4 = *(s32 *)(var_16 + 0x10);
        if (temp_4 != 0) {
            ClothSimStep_185170(temp_4);
        }
        var_16 = *(u8 **)var_16;
    }
}
