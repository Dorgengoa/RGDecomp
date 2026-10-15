#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

s32 ConstructNewArray_100710(s32, u8 *, s32, s32, s32);              /* extern */
s32 MemStackStrDup_14cf10(s32, s32);                         /* extern */
s32 MemStackNew_14e1b0(s32, s32);                         /* extern */
s32 SlotGetInt_15f720(s32);                              /* extern */
s32 VariantGetInt_15f780();                                 /* extern */
extern u8 *D_004812F4;
extern s32 D_004812F8;
extern s32 D_00481308;
extern void MapLightSetCtor_1923a0(void);

s32 MapSceneCfgLightGroup_193410(s64 *arg0) {
    u8 *var_19;
    s32 temp_17;
    s32 temp_18;
    s32 temp_2;
    u8 *temp_16;
    s32 temp_16_2;
    s64 *p;

    arg0++;
    temp_17 = VariantGetInt_15f780();
    temp_2 = SlotGetInt_15f720((s32)arg0);
    temp_18 = D_004812F8;
    temp_16 = D_004812F4;
    if (temp_17 < 0 || temp_17 >= 0x10) {
        var_19 = 0;
    } else {
        var_19 = temp_16 + (temp_17 * 0xC) + 0xA8;
    }
    if (var_19 == 0) {
        var_19 = 0;
    } else {
        (*(s32 *)((u8 *)var_19 + 0x0)) = MemStackStrDup_14cf10(temp_2, temp_18);
        temp_16_2 = (*(s32 *)((u8 *)temp_16 + 0x9C));
        (*(s32 *)((u8 *)var_19 + 0x4)) = temp_16_2;
        (*(s32 *)((u8 *)var_19 + 0x8)) = ConstructNewArray_100710(MemStackNew_14e1b0((temp_16_2 * 0x1D0) + 0x10, temp_18), (u8 *)&MapLightSetCtor_1923a0, 0, 0x1D0, temp_16_2);
    }
    if (var_19 != 0) {
        D_00481308 = temp_17;
    }
    return 1;
}
