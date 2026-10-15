#include "types.h"
#include "vec.h"

extern void VariantReadVec3_15f6c0(void *, s32);
extern s32 VariantGetInt_15f780(s32);
extern u8 *D_00481154;
extern s32 D_00481170;

s32 DynBoundingBoxCmd_167840(s64 *arg0, s32 arg1) {
    s32 temp_4;
    u8 *var_18;
    u8 *g;

    temp_4 = D_00481170;
    g = D_00481154;
    D_00481170 = temp_4 + 1;
    if ((temp_4 < 0) || (temp_4 >= *(s32 *)(g + 0xE4))) {
        var_18 = NULL;
    } else {
        var_18 = *(u8 **)(g + 0xE8) + (temp_4 * 0x30);
    }
    if (var_18 == NULL) {
        return 0;
    }
    *(s32 *)(var_18 + 0x20) = VariantGetInt_15f780((s32)arg0++);
    if (arg1 >= 4) {
        VariantReadVec3_15f6c0(var_18, (s32)arg0);
        arg0 += 3;
        *(u128 *)(var_18 + 0x10) = *(u128 *)(var_18 + 0x0);
    }
    if (arg1 >= 7) {
        VariantReadVec3_15f6c0(var_18 + 0x10, (s32)arg0);
    }
    return 1;
}
