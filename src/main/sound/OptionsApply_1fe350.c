#include "types.h"

typedef struct Cfg1fe350 {
    u8 pad00[0x12];
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
} Cfg1fe350;

typedef struct A1fe350 {
    u8 pad00[0xC];
    Cfg1fe350 *m0C;
} A1fe350;

extern A1fe350 *GetGameData_1fede0(void);
extern void *GetStreamMgr_207ea0(void);
extern void *GetCurrentScene_1f5be0(void);
extern void SoundSetOutputMode_1bb3e0(s32 f);
extern void SoundStreamSetOutputMode_1bc6e0(s32 f);
extern void StreamMgrSetChanGain_1d63f0(void *o, s32 i, f32 v);
extern void GameSceneSoundSetOptionVolume_1d11f0(void *o, f32 v);
extern void CameraSetOptionFlag_309cf0(s32 f);

void OptionsApply_1fe350(void)
{
    A1fe350 *a;
    void *b;
    void *c;

    a = GetGameData_1fede0();
    b = GetStreamMgr_207ea0();
    c = GetCurrentScene_1f5be0();
    SoundSetOutputMode_1bb3e0(a->m0C->m12 == 0);
    SoundStreamSetOutputMode_1bc6e0(a->m0C->m12 == 0);
    StreamMgrSetChanGain_1d63f0(b, 0, (f32)a->m0C->m14 / 10.0f);
    GameSceneSoundSetOptionVolume_1d11f0(c, (f32)a->m0C->m16 / 10.0f);
    StreamMgrSetChanGain_1d63f0(b, 1, (f32)a->m0C->m18 / 10.0f);
    StreamMgrSetChanGain_1d63f0(b, 2, (f32)a->m0C->m18 / 10.0f);
    CameraSetOptionFlag_309cf0((a->m0C->m1A & 1) == 1);
}
