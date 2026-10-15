#include "types.h"

extern void *memset(void *d, s32 c, s32 n);
extern void SoundSlotInit_1d2230(void *e);
extern void SoundSlotSetIndex_1d20f0(void *e, s32 i);
extern void SoundSlotSetBankId_1d2100(void *e, s32 i);
extern void SoundSlotFree_1d21e0(void *e);
extern void GameSceneEmitterSoundsReset_1d01d0(void *p);
extern void SoundCategoryFadeInit_1b60c0(void *p);
extern void GameSceneSoundSlot2SetVolume_1d0650(void *p, f32 t);
extern void GameSceneSoundSlot3SetVolume_1d0640(void *p, f32 t);
extern void GameSceneSoundNoteListInit_1d14e0(void *p);
extern void SoundBankStopAll_1bad70(s32 i);

void GameSceneSoundInit_1d1260(void *p)
{
    u8 *q;
    s32 i;
    u8 *e;

    q = (u8 *)p;
    *(s32 *)(q + 0x5E18) = 0;
    *(s32 *)(q + 0xA61C) = 0;
    memset(q + 0xB468, 0, 0x24);
    *(q + 0xB48C) = 0;
    *(q + 0xB48D) = 0;
    *(f32 *)(q + 0xB490) = 1.0f;
    *(q + 0xB498) = 0;
    *(f32 *)(q + 0xB494) = 1.0f;
    *(s32 *)(q + 0xB49C) = -1;
    *(s32 *)(q + 0xB4A0) = -1;
    *(s32 *)(q + 0xB4A4) = -1;
    *(s8 *)(q + 0xB4A8) = -1;
    *(f32 *)(q + 0xB4AC) = 1.0f;
    *(f32 *)(q + 0xB4B0) = 1.0f;
    *(s32 *)(q + 0xB4B4) = 0;
    *(s32 *)(q + 0xB4B8) = 0;
    for (i = 0; i < 7; i++) {
        e = q + i * 0x88 + 0xB0B0;
        SoundSlotInit_1d2230(e);
        SoundSlotSetIndex_1d20f0(e, i);
    }
    SoundSlotSetBankId_1d2100(q + 0xB0B0, 6);
    SoundSlotSetBankId_1d2100(q + 0xB138, 3);
    SoundSlotSetBankId_1d2100(q + 0xB1C0, 2);
    SoundSlotSetBankId_1d2100(q + 0xB248, 0xC);
    SoundSlotSetBankId_1d2100(q + 0xB2D0, 1);
    SoundSlotSetBankId_1d2100(q + 0xB358, 9);
    SoundSlotSetBankId_1d2100(q + 0xB3E0, 4);
    for (i = 0; i < 7; i++) {
        SoundSlotFree_1d21e0(q + i * 0x88 + 0xB0B0);
    }
    GameSceneEmitterSoundsReset_1d01d0(q);
    SoundCategoryFadeInit_1b60c0(q + 0xAE20);
    GameSceneSoundSlot2SetVolume_1d0650(q, 0.0f);
    GameSceneSoundSlot3SetVolume_1d0640(q, 0.0f);
    GameSceneSoundNoteListInit_1d14e0(q);
    SoundBankStopAll_1bad70(-1);
}
