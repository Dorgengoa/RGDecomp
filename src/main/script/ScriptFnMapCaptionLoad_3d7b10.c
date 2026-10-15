#include "types.h"

s32 MapMgrCaptionLoad_1e2f10(s32, s32, s32);
s32 GetGameMode_1f59c0(void);
s32 GetMapMgr_201a90(void);
void VariantSetS32_36f040(s32, s32, s32);
s32 VariantGetS32_36fb30(s32);
s32 VariantGetS16_36fcc0(s32);
extern s32 D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;

void ScriptFnMapCaptionLoad_3d7b10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 t;
    s32 f;
    u8 r;
    s32 p;

    if (arg0 == 0) return;
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0 || D_00483968 == 0) return;
    if (arg3 == 0 || arg2 <= 0) return;
    {
        t = (s16)VariantGetS16_36fcc0(arg3);
        f = 0;
        if (arg2 >= 2) f = VariantGetS32_36fb30(arg3 + 0x38) != 0;
        if (f || GetGameMode_1f59c0() == 6) {
            r = 0;
            p = GetMapMgr_201a90();
            if (p != 0) r = MapMgrCaptionLoad_1e2f10(p, t, 1);
            VariantSetS32_36f040(arg0, r, 1);
        }
    }
}
