/* rgp:protos */
#line 1
#include "types.h"

struct S39b490 { u8 pad[0x18]; s32 unk18; u8 pad1C[4]; s32 unk20; u8 pad24[8]; s32 unk2C; };

extern "C" {
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 GetDrawCtx_15de80(void);
extern void Character2DrawTintedMaybe_1ae620(s32, f32, f32, f32, f32);
extern void Character2DrawWithOwnLightMaybe_1ae720(s32);
extern s32 GetGameMode_1f59c0(void);
extern f32 InsectCageSlotGetPulseLevel_39b360(S39b490 *);
extern s32 InsectCageSlotGetState_39bb00(void *);

void InsectCageSlotDraw_39b490(S39b490 *arg0) {
    bool b;

    if (((short)InsectCageSlotGetState_39bb00((void *)arg0)) != 2) {
        return;
    }
    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), arg0->unk20, 1.0f);
    b = true;
    if (GetGameMode_1f59c0() == 14) {
        b = false;
    }
    if (arg0->unk2C > 0 && b) {
        Character2DrawTintedMaybe_1ae620(arg0->unk18, 255.0f, 255.0f, 255.0f, 1.0f - InsectCageSlotGetPulseLevel_39b360(arg0));
        return;
    }
    Character2DrawWithOwnLightMaybe_1ae720(arg0->unk18);
}
}
