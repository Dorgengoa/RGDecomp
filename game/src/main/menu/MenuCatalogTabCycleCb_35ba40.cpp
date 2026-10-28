#include "types.h"

extern "C" {
extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PadIsRepeatTriggered_183dd0(void *, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void MenuCatalogSaveTabCursor_35ee20(void *, s32);
extern void MenuCatalogTabSpritesUpdate_3603e0(void *);
extern void MenuCatalogTabSetup_360590(void *);
extern void *D_00482388;
extern u8 D_004B2570[];
}



extern "C" s32 MenuCatalogTabCycleCb_35ba40(void)
{
    u8 *p;
    s32 h;
    s32 idx;
    bool changed;
    s32 cur;
    bool b;
    s32 k;

k = *(s32 *)((u8 *)D_00482388 + 0x284);
    if (k == 3) {
        b = 1;
    } else if (k == 4) {
        b = 1;
    } else {
        b = 0;
    }
    if (b) {
        return 1;
    }
    p = D_004B2570;
    h = SceneSoundGetSlot0HandleCur_207df0();
    idx = *(s32 *)((u8 *)D_00482388 + 0x284);
    changed = 0;
    if (PadIsTriggered_1839f0(p, 4) != 0) {
        cur = *(s32 *)((u8 *)D_00482388 + 0x284);
        if (cur > 0) {
            idx = cur - 1;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(p, 4) == 0) {
            idx = 2;
            changed = 1;
        }
    } else if (PadIsTriggered_1839f0(p, 8) != 0) {
        cur = *(s32 *)((u8 *)D_00482388 + 0x284);
        if (cur < 2) {
            idx = cur + 1;
            changed = 1;
        } else if (PadIsRepeatTriggered_183dd0(p, 8) == 0) {
            idx = 0;
            changed = 1;
        }
    }
    if (changed) {
        MenuCatalogSaveTabCursor_35ee20(D_00482388, idx);
        *(s32 *)((u8 *)D_00482388 + 0x284) = idx;
        MenuCatalogTabSetup_360590(D_00482388);
        MenuCatalogTabSpritesUpdate_3603e0(D_00482388);
        SoundPlayScaledVolume_1b9520(h, 0xB, 0, 1.0f);
    }
    return 1;
}
