#include "types.h"

void UiSetSpriteSizeUvSize_28f670(u8 *, u16, s32, s32, s32, s32, s32);
void UiSetSpriteU_28f930(u8 *, u16, s32, s32);
void UiMoveWidgetUniform_290f50(u8 *, u16, s32, s32, s32, f32);
void UiSetWidgetsVisibleById_291110(u8 *, s32, s32, s32);
void UiSetWidgetParent_2911a0(u8 *, s32, u16);
void MainMenuPanelSetWidgetTex_297850(s16, u8 *, s16, s32, s32);
s32 TopMenuRow6UnlockedMaybe_29ac20(void);
s32 TopMenuRow5UnlockedMaybe_29ac50(void);
s32 TopMenuIsHunterUnlocked_29ac90(void);
extern u8 D_00461198[16];
extern u8 D_004611A8[16];
extern f32 D_0047D488;
extern u8 D_004DB1B0[0x100];

s32 TopMenuLayoutEntries_294ad0(u8 *arg0) {
    f32 x;
    f32 y;
    s32 i;
    u16 id;
    s32 t;
    s32 k;

    for (i = 0; i < 8; i++) {
        t = (u16)(i + 0x16);
        if (*(s16 *)(arg0 + 0x12) == i) {
            id = t;
            x = 43.0f;
            UiSetSpriteSizeUvSize_28f670(D_004DB1B0, id, 0, 0, 0, 0, 0);
            y = (i / 2) * 64;
            UiSetWidgetParent_2911a0(D_004DB1B0, 0x15, id);
            UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x15, 1, 1);
        } else {
            id = t;
            UiSetSpriteSizeUvSize_28f670(D_004DB1B0, id, 0x74, 0x1A, 4, 4, 0);
            x = 33.0f;
            y = (i / 2) * 64 + 0x20;
        }
        k = i * 39;
        UiMoveWidgetUniform_290f50(D_004DB1B0, id, (s32)x, k + 0x50, 0, D_0047D488);
        UiMoveWidgetUniform_290f50(D_004DB1B0, i + 0xD, (s32)(3.0f + x), k + 0x53, 0, D_0047D488);
        id = i + 0x39;
        UiSetSpriteU_28f930(D_004DB1B0, id, (s32)y, 0);
        if (i == 4) {
            if (TopMenuIsHunterUnlocked_29ac90() == 0) {
                MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
            } else {
                MainMenuPanelSetWidgetTex_297850(id, D_004611A8, (s16)y, 0xC1, 0x1F);
            }
        } else if (i == 5) {
            if (TopMenuRow5UnlockedMaybe_29ac50() == 0) {
                MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
            } else {
                MainMenuPanelSetWidgetTex_297850(id, D_004611A8, (s16)y, 0xE1, 0x1F);
            }
        } else if (i == 6) {
            if (TopMenuRow6UnlockedMaybe_29ac20() == 0) {
                MainMenuPanelSetWidgetTex_297850(id, D_00461198, 0x60, 0x60, 0x20);
            } else {
                MainMenuPanelSetWidgetTex_297850(id, D_004611A8, (s16)y, 0xC1, 0x1F);
            }
        }
    }
    return 1;
}
