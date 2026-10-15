/* PARKED s15i: m2c draft references an unresolved pseudo-variable
 * (`unksp44 +=`, a compound accumulate into an s128/f32 local m2c's SSA lost
 * track of) plus an s128 local; 0 round trips spent. Needs
 * asm/matchings/main/StatusEffectSlotUpdate_33c3d0.s read by hand to identify what unksp44
 * actually is (likely a 4th word of the sp40 quadword) before writing C.
 * Not attempted. */
/* s49m: MATCH */
#include "types.h"
#pragma opt_propagation off

typedef unsigned __int128 u128;
typedef struct { f32 x, y, z, w; } V4;

typedef struct Eff {
    u8 pad0[0x10];
    s16 active;
    s16 mode;
    s16 target;
    s16 timer;
    s16 snd;
    s16 sndarg;
    u8 pad1C[4];
    s32 unk20;
} Eff;

typedef struct Actor {
    u8 pad0[0x180];
    V4 pos;
    u8 pad190[0x4CC - 0x190];
    f32 height;
} Actor;

extern u8 *GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlot5GetHandle_1d0790(u8 *);
extern void SoundNoteListPush_1b4cd0(u8 *, s32, s32, s32, s32, f32, f32);
extern void StatusEffectOrbitIconsSpin_33d040(Eff *);
extern void StatusEffectSlotLightningTick_33cfe0(Eff *);
extern void StatusEffectHitIconsUpdate_33c940(Eff *);
extern s32 GetStaticScene_1c6c70(void);
extern Actor *ObjRecGetLiveObject_1c4a90(s32, s32);
extern s32 GetEffectMgr_2d9040(void);
extern void StatusEffectSlotStop_33c2b0(Eff *);
extern f64 fptodp(f32);
extern f64 dpmul(f64, f64);
extern f32 dptofp(f64);
extern void EffectSetPos_2e0bb0(s32, void *, V4 *);
extern f64 D_0047D190;
extern f64 D_0047D1C0;

void StatusEffectSlotUpdate_33c3d0(Eff *o)
{
    V4 p;
    u8 *b;
    u8 *q;
    Actor *a;
    s32 c;

    if (o->active == 0) {
        return;
    }
    if (o->snd > 0) {
        b = GetCurrentScene_1f5be0();
        q = b + 0xB0A4;
        SoundNoteListPush_1b4cd0(q, GameSceneSoundSlot5GetHandle_1d0790(b), o->snd, 2, o->sndarg, 1.0f, 0.0f);
    }
    if (o->mode == 1 || o->mode == 3) {
        StatusEffectOrbitIconsSpin_33d040(o);
        return;
    }
    if (o->mode == 4) {
        StatusEffectSlotLightningTick_33cfe0(o);
        return;
    }
    if (o->mode == 5) {
        StatusEffectHitIconsUpdate_33c940(o);
        return;
    }
    a = ObjRecGetLiveObject_1c4a90(GetStaticScene_1c6c70(), o->target);
    if (a == NULL) {
        return;
    }
    c = GetEffectMgr_2d9040();
    if (o->timer > 0) {
        o->timer = o->timer - 1;
        if (o->timer <= 0) {
            StatusEffectSlotStop_33c2b0(o);
            o->timer = -1;
            o->active = 0;
            return;
        }
    }
    *(u128 *)&p = *(u128 *)&a->pos;
    p.y = p.y + dptofp(dpmul(D_0047D1C0, dpmul(D_0047D190, fptodp(a->height))));
    if (o->unk20 != -1) {
        EffectSetPos_2e0bb0(c, (u8 *)o + 0x1C, &p);
    }
}
