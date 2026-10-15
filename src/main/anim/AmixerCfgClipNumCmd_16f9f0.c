#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern s32 VariantGetInt_15f780(void);
extern s32 D_0048118C;
extern void *D_00481194;
extern void AmixerClipCtor_16fa80(void);

s32 AmixerCfgClipNumCmd_16f9f0(void)
{
    s32 temp_2;
    s32 temp_2_2;
    u8 *temp_16;
    s32 temp_5;

    if (D_00481194 == NULL) {
        return 0;
    }
    temp_2 = VariantGetInt_15f780();
    temp_5 = D_0048118C;
    temp_16 = (u8 *)D_00481194;
    if (temp_2 > 0) {
        temp_2_2 = ConstructNewArray_100710(MemStackNew_14e1b0((temp_2 * 0x24) + 0x10, temp_5), (void *)AmixerClipCtor_16fa80, 0, 0x24, temp_2);
        *(s32 *)(temp_16 + 4) = temp_2_2;
        if (temp_2_2 != 0) {
            *(s32 *)(temp_16 + 0) = temp_2;
        }
    }
    return 1;
}
