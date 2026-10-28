/* rgp:protos */
#line 1
#include "types.h"

struct Base249 {
    u8 pad0[0x58];
};

struct Ent249 {
    s32 f[4];
};

struct Obj249 : Base249 {
    VC_VPTR_MEMBER; void f0() { VCM0(void, 0x8); }
    u8 pad5c[0x944];
    Ent249 ent[12];
    u32 flags;
};

extern "C" {
u8 *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberId_3c2490(s32, s32);
void ObjRecSetFlag2_1c3e80(u8 *, s32, s32);
void ObjRecClearFlag2_1c3e40(u8 *, s32, s32);
void ParamTableSetAlpha_1cfb10(u8 *, s32, f32);
s32 ObjRecGetLiveObject_1c4a90(u8 *, s32);
void ModelObjTexAnimResetAll_1ac450(s32);
void ModelObjTexAnimStartByName_1ac590(s32, u8 *);
void ObjRecSetValue_1c3d60(u8 *, s32, s32, s32);
void ScreenFadeIn_1cf740(u8 *, s32);
void ScreenFadeSetOverlayMaybe_1cf540(u8 *, s32, s32, s32);
void GameSceneDofSetOverridePreset_2f6ab0(void);
void EventCleanupCastMesSound_249440(Obj249 *, u8 *);
void CameraScenePopApplyFov_309f10(void);
void PauseSetAllowed_2f6640(s32);
void GameSceneCBlurResetMode2Maybe_2f1da0(void);
void GameSceneTintReset_1ce980(u8 *);
void TaskTableRestoreOrder_27bed0(void);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
void ScriptVmReset_176bd0(Obj249 *);
extern u8 D_0045EB60[0x400];
}

static inline bool Ok(s32 t)
{
    return t >= 0 && t < 12;
}

static inline s32 Idx(s32 t, s32 k)
{
    if (Ok(t)) {
        return t * 4 + k;
    }
    return -1;
}

extern "C" void EventPlayerEnd_249480(Obj249 *self, u8 *wk)
{
    u8 *g;
    s32 n;
    s32 i;
    u8 *e;
    s32 o;
    s32 t;
    u32 v;
    s32 k;


    g = GetGameData_1fede0();
    n = PartyCountMembers_3c2010(*(s32 *)(g + 0x18), 1, 1);
    for (i = 0; i < n; i++) {
        t = ((short)PartyGetMemberId_3c2490(*(s32 *)(g + 0x18), i));
        ObjRecSetFlag2_1c3e80(wk, 1, t);
        ParamTableSetAlpha_1cfb10(wk, t, 1.0f);
        e = (u8 *)self + i * 16;
        if (*(s32 *)(e + 0x9A0) != 0) {
            ObjRecSetFlag2_1c3e80(wk, 1, Idx(t, 0xC));
        } else {
            ObjRecClearFlag2_1c3e40(wk, 1, Idx(t, 0xC));
        }
        if (*(s32 *)(e + 0x9A4) != 0) {
            ObjRecSetFlag2_1c3e80(wk, 1, Idx(t, 0xD));
        } else {
            ObjRecClearFlag2_1c3e40(wk, 1, Idx(t, 0xD));
        }
        if (*(s32 *)(e + 0x9A8) != 0) {
            ObjRecSetFlag2_1c3e80(wk, 1, Idx(t, 0xE));
        } else {
            ObjRecClearFlag2_1c3e40(wk, 1, Idx(t, 0xE));
        }
        if (*(s32 *)(e + 0x9AC) != 0) {
            ObjRecSetFlag2_1c3e80(wk, 1, Idx(t, 0xF));
        } else {
            ObjRecClearFlag2_1c3e40(wk, 1, Idx(t, 0xF));
        }
        if (t == 7) {
            ObjRecSetFlag2_1c3e80(wk, 1, Idx(t, 0xC));
        }
        o = ObjRecGetLiveObject_1c4a90(wk, t);
        if (o != 0) {
            ModelObjTexAnimResetAll_1ac450(o);
            ModelObjTexAnimStartByName_1ac590(o, D_0045EB60);
        }
        ObjRecSetValue_1c3d60(wk, 1, t, 0);
    }
    v = self->flags;
    if (v & 0x10) {
        if (!(v & 8)) {
            ScreenFadeIn_1cf740(wk, 0xA);
        } else {
            self->flags = v & ~8;
        }
    }
    *(f32 *)(wk + 0xB55C) = -1.0f;
    ScreenFadeSetOverlayMaybe_1cf540(wk, 0, 0, 0);
    GameSceneDofSetOverridePreset_2f6ab0();
    EventCleanupCastMesSound_249440(self, wk);
    self->f0();
    for (k = 0xC0; k <= 0xDF; k++) {
        if (ObjRecGetLiveObject_1c4a90(wk, k) != 0) {
            ObjRecSetFlag2_1c3e80(wk, 1, k);
        }
    }
    CameraScenePopApplyFov_309f10();
    PauseSetAllowed_2f6640(1);
    GameSceneCBlurResetMode2Maybe_2f1da0();
    GameSceneTintReset_1ce980(wk);
    TaskTableRestoreOrder_27bed0();
    StateFlagSet_3ccb70(*(s32 *)(g + 0x10), 0x7ED, 0, 1);
    ScriptVmReset_176bd0(self);
}
