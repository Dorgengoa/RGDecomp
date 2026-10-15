#include "types.h"

f32 VariantGetFloat_15f740(s32, s32);
s32 VariantGetInt_15f780(s32);

typedef struct {
    u8 pad0[0xa0];
    s32 unkA0;
    u8 padA4[0x20];
    s32 unkC4;
    u8 *unkC8;
} T1683;

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
} R1683;

extern T1683 *D_00481154;
extern s32 D_00481184;

s32 DynFollowVertexCmd_1683f0(s64 *arg0, s32 arg1) {
    s32 temp_16;
    s32 temp_2;
    s32 temp_5;
    s32 var_3;
    R1683 *var_19;
    T1683 *g;


    temp_16 = VariantGetInt_15f780((s32)arg0++);
    temp_2 = VariantGetInt_15f780((s32)arg0++);
    g = D_00481154;
    if ((temp_2 < 0) || (temp_2 >= g->unkA0)) {
        var_3 = 0;
    } else {
        var_3 = 1;
    }
    if (var_3 == 0) {
        return 0;
    }
    temp_5 = D_00481184;
    D_00481184 = temp_5 + 1;
    if ((temp_5 < 0) || (temp_5 >= g->unkC4)) {
        var_19 = NULL;
    } else {
        var_19 = (R1683 *)(g->unkC8 + (temp_5 * 0xC));
    }
    if (var_19 == NULL) {
        return 0;
    }
    var_19->unk0 = temp_16;
    var_19->unk4 = temp_2;
    var_19->unk8 = 1.0f;
    if (arg1 >= 3) {
        var_19->unk8 = VariantGetFloat_15f740((s32)arg0, temp_5);
    }
    return 1;
}
