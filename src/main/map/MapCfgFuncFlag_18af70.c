#include "types.h"

extern f32 VariantGetFloat_15f740(s32 arg0);
extern s32 VariantGetInt_15f780(s32 arg0);
extern s32 D_004812D8;
extern void *D_004812DC;

s32 MapCfgFuncFlag_18af70(s64 *arg0)
{
    if (D_004812D8 == 0) {
        return 0;
    }
    if (D_004812DC == NULL) {
        return 1;
    }
    *(s32 *)((u8 *)D_004812DC + 0x54) = VariantGetInt_15f780((s32)arg0++);
    *(s32 *)((u8 *)D_004812DC + 0x50) = VariantGetInt_15f780((s32)arg0++);
    *(f32 *)((u8 *)D_004812DC + 0x58) = VariantGetFloat_15f740((s32)arg0++);
    *(f32 *)((u8 *)D_004812DC + 0x5C) = VariantGetFloat_15f740((s32)arg0);
    return 1;
}
