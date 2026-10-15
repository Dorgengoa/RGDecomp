#pragma opt_propagation off
#include "types.h"

typedef struct Pos { s16 x; s16 y; } Pos;
typedef struct Entry {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    s16 mC;
    s16 arr[8];
    Pos pos;
    u8 m22;
    u8 m23;
} Entry;
typedef struct Sys { u8 pad[0xB468]; Entry cur; } Sys;

extern "C" {
extern char D_004B2570[];
void PadWaitReady_1849e0(char *s);
void SoundSetReverb_1bb610(s32 a, u8 b, u8 c);
void GameSceneAmbientSetVolume_1d0460(Sys *s, f32 f);
s32 GameSceneAmbientRequest_1d0470(Sys *s, s16 v);
void GameSceneSoundSlot6RequestLoad_1d0670(Sys *s, s16 x, s16 y);
void GameSceneSoundSlot5RequestLoad_1d0690(Sys *s, s16 v);
void GameSceneSoundSlot4RequestLoad_1d06a0(Sys *s, s16 v);
void GameSceneSoundSlot1RequestLoad_1d06b0(Sys *s, s16 v);
void GameSceneSoundSlot0RequestLoad_1d06c0(Sys *s, s32 v);
void GameSceneSoundSlot6Free_1d0850(Sys *s);
s32 GameSceneSoundEnvGetCurPresetId_1d1160(Sys *s);
s32 GameSceneSoundEnvIsLocked_1d11b0(void);
Entry *GameSceneSoundEnvFindPreset_1d1540(Sys *s, s32 id);
}

extern "C" s32 GameSceneSoundEnvApplyPreset_1d0e30(Sys *s, s32 id, s32 force, s32 dbg)
{
    Entry *e;

    if (GameSceneSoundEnvIsLocked_1d11b0() != 0) {
        return 0;
    }
    if ((e = GameSceneSoundEnvFindPreset_1d1540(s, id)) == 0) {
        return 0;
    }
    if (id == GameSceneSoundEnvGetCurPresetId_1d1160(s)) {
        if (force != 0) {
            GameSceneSoundSlot6Free_1d0850(s);
            { s16 x = s->cur.pos.x; s16 y = s->cur.pos.y; GameSceneSoundSlot6RequestLoad_1d0670(s, x, y); }
        }
        return 0;
    }
    GameSceneSoundSlot0RequestLoad_1d06c0(s, 0);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    GameSceneSoundSlot1RequestLoad_1d06b0(s, e->m4);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    GameSceneSoundSlot5RequestLoad_1d0690(s, e->m6);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    GameSceneSoundSlot4RequestLoad_1d06a0(s, e->arr[0]);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    if (GameSceneAmbientRequest_1d0470(s, e->m8) != 0) {
        f32 f;
        if (e->mA >= 0) {
            f = 1.0f;
        } else {
            f = (f32)e->mC / 127.0f;
        }
        GameSceneAmbientSetVolume_1d0460(s, f);
    }
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    if (force != 0 || e->pos.x != s->cur.pos.x || e->pos.y != s->cur.pos.y) {
        GameSceneSoundSlot6Free_1d0850(s);
    }
    GameSceneSoundSlot6RequestLoad_1d0670(s, e->pos.x, e->pos.y);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    SoundSetReverb_1bb610(0, e->m22, e->m23);
    SoundSetReverb_1bb610(1, e->m22, e->m23);
    if (dbg) {
        PadWaitReady_1849e0(D_004B2570);
    }
    s->cur = *e;
    return 1;
}
