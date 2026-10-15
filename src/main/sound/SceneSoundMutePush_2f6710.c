#include "types.h"

/* MAIN SceneSoundMutePush_2f6710 -- push; the `bgtz` skip means the body is the
   `<= 0` arm, and the increment's store sits in its delay slot. */

extern s32 D_00482768;
extern f32 D_0047EF70;
extern f32 D_0047EF74;
extern f32 D_0047EF78;
extern f32 D_0047EF7C;

extern void *GetCurrentScene_1f5be0(void);
extern f32 GameSceneSoundSlot5GetVolume_1d0760(void *);
extern f32 GameSceneSoundGetVolume_1d0540(void *);
extern f32 GameSceneSoundSlot4GetVolume_1d0770(void *);
extern f32 GameSceneSoundGetVolumeScale_1d11e0(void *);
extern void GameSceneSoundSlot5SetVolume_1d0620(void *, f32);
extern void GameSceneSoundSetVolumeNow_1d0400(void *, f32);
extern void GameSceneSoundSlot4SetVolume_1d0630(void *, f32);
extern void SoundNoteListSetVolumeScale_1b4ab0(void *, f32);

void SceneSoundMutePush_2f6710(void)
{
    s32 n;
    u8 *o;

    n = D_00482768 + 1;
    D_00482768 = n;
    if (n <= 0) {
        o = GetCurrentScene_1f5be0();
        D_0047EF70 = GameSceneSoundSlot5GetVolume_1d0760(o);
        D_0047EF74 = GameSceneSoundGetVolume_1d0540(o);
        D_0047EF78 = GameSceneSoundSlot4GetVolume_1d0770(o);
        D_0047EF7C = GameSceneSoundGetVolumeScale_1d11e0(o);
        GameSceneSoundSlot5SetVolume_1d0620(o, 0.0f);
        GameSceneSoundSetVolumeNow_1d0400(o, 0.0f);
        GameSceneSoundSlot4SetVolume_1d0630(o, 0.0f);
        SoundNoteListSetVolumeScale_1b4ab0(o + 0xB0A4, 0.0f);
    }
}
