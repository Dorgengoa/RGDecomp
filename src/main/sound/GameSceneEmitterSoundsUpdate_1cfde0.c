#pragma optimization_level 3
#include "types.h"

typedef struct Slot {
    s16 id;
    s16 cnt;
    f32 vol;
    f32 pitch;
    f32 lastVol;
    f32 lastPitch;
} Slot;

typedef struct T1cfde0 {
    u8 pad0[0xB2D0];
    u8 snd[0x1EC];
    Slot slots[8];
} T1cfde0;

extern s32 MapAreaModelCollectSoundEmitters_1873e0(s32, s32 *, f32 *, f32 *, s32);
extern void SoundStopEntry_1b8bc0(s32, s32, s32);
extern void SoundPlayScaledVolPan_1b9680(s32, s32, s32, f32, f32);
extern void SoundSetEntryVolumeScaled_1b9820(s32, s32, s32, f32);
extern void SoundSetPanFloat_1b9a50(s32, s32, s32, f32);
extern void SoundBankStopAll_1bad70(s32);
extern s32 ObjRecCollectLiveObjects_1c5150(T1cfde0 *, s32 *, s32);
extern void GameSceneEmitterSoundsReset_1d01d0(T1cfde0 *);
extern f32 SoundSlotGetVolume_1d2120(void *);
extern s32 SoundSlotGetBankId_1d2130(void *);
extern s32 SoundSlotGetHandle_1d2150(void *);
extern s32 SoundSlotIsMuted_1d21d0(void *);

static inline void maxto(f32 *d, f32 *v) { f32 m = *d; if (m <= *v) m = *v; *d = m; }
static inline void maxto2(f32 *d, f32 v) { f32 m = *d; if (m <= v) m = v; *d = m; }
#define MAXTO(d, v) { f32 *d_ = (d); f32 *v_ = (v); f32 m_ = *d_; if (m_ <= *v_) m_ = *v_; *d_ = m_; }

void GameSceneEmitterSoundsUpdate_1cfde0(T1cfde0 *self) {
    s32 list[20];
    s32 ids[8];
    f32 vols[8];
    f32 pitches[8];
    s32 n;
    s32 cnt;
    f32 f;
    void *snd;
    s32 j;
    s32 k;
    Slot *p;
    s32 s;
    f32 v;
    s32 i;

    snd = self->snd;
    p = self->slots;
    for (i = 0; i < 8; i++) {
        p->cnt = 0;
        p->vol = 0.0f;
        p->pitch = 0.0f;
        p++;
    }
    n = ObjRecCollectLiveObjects_1c5150(self, list, 0x14);
    if (n <= 0) {
        GameSceneEmitterSoundsReset_1d01d0(self);
        SoundBankStopAll_1bad70(SoundSlotGetBankId_1d2130(snd));
        return;
    }
    for (j = 0; j < n; j++) {
        if (list[j] == 0) continue;
        cnt = MapAreaModelCollectSoundEmitters_1873e0(list[j], ids, vols, pitches, 8);
        for (k = 0; k < cnt; k++) {
            if (ids[k] < 0) continue;
            for (s = 0; s < 8; s++) {
                if (self->slots[s].id == ids[k]) break;
            }
            if (s >= 8) {
                for (s = 0; s < 8; s++) {
                    if (self->slots[s].id < 0) {
                        self->slots[s].id = ids[k];
                        SoundPlayScaledVolPan_1b9680(SoundSlotGetHandle_1d2150(snd), self->slots[s].id, s % 31 + 1, 0.0f, 0.0f);
                        break;
                    }
                }
            }
            if (s >= 0 && s < 8) {
                self->slots[s].vol = (self->slots[s].vol > vols[k]) ? self->slots[s].vol : vols[k];
                self->slots[s].pitch += pitches[k];
                self->slots[s].cnt++;
            }
        }
    }
    if (SoundSlotIsMuted_1d21d0(snd) != 0) {
        f = 0.0f;
    } else {
        f = SoundSlotGetVolume_1d2120(snd);
    }
    p = self->slots;
    for (i = 0; i < 8; i++, p++) {
        s16 id = p->id;
        if (id < 0) continue;
        if (p->cnt <= 0) {
            SoundStopEntry_1b8bc0(SoundSlotGetHandle_1d2150(snd), id, i % 31 + 1);
            p->id = -1;
            p->cnt = 0;
            p->vol = 0.0f;
            p->pitch = 0.0f;
            p->lastVol = -1.0f;
            p->lastPitch = -1.0f;
        } else {
            p->pitch = p->pitch / (f32)p->cnt;
            v = p->vol * f;
            if (v != p->lastVol) {
                SoundSetEntryVolumeScaled_1b9820(SoundSlotGetHandle_1d2150(snd), p->id, i % 31 + 1, v);
                p->lastVol = v;
            }
            v = p->pitch;
            if (v != p->lastPitch) {
                SoundSetPanFloat_1b9a50(SoundSlotGetHandle_1d2150(snd), p->id, i % 31 + 1, v);
                p->lastPitch = p->pitch;
            }
        }
    }
}
