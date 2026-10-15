/* PARKED at triage (0 round trips): m2c's draft references `sp5C` in the
 * loop condition (`if (sp5C >= var_19)`) but only `sp58` is declared --
 * sp5C is an undeclared adjacent field m2c never named. Needs a raw-asm
 * trace of the stack frame. Deferred. See asm/matchings/main/MenuMobPreviewDraw_35fa50.s. */
/* s49m: MATCH */
#include "types.h"

class Model {
    u8 pad0[0x1B0];
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
};

struct Range {
    s32 lo;
    s32 hi;
};

struct Self {
    u8 pad0[0x5C];
    u8 list[0x1E8];
    u8 flag244;
    u8 pad245[0xB];
    Model *model;
    u8 pad254[0x30];
    s32 mode;
};

extern "C" {
extern s32 D_004823D4;
u8 *GetDrawCtx_15de80(void);
void DrawEnvPush_144830(u8 *);
void DrawEnvPop_144800(u8 *);
void DrawEnvSetScissor_157580(s32, s32, s32, s32, s32);
void DrawListAddEnv_1421d0(u8 *);
void DrawListAddTexLoad_1418c0(u8 *, f32, s32);
void CameraSetViewFromCameraBase_142dd0(u8 *, s32);
void DrawListAddCameraMatrixPacket_1481b0(u8 *);
void DrawListAddViewPacket_1482e0(u8 *);
void Character2DrawTintedMaybe_1ae620(Model *, f32, f32, f32, f32);
void memset(void *, s32, s32);
void EffTableBuildIndexMaybe_1a04d0(u8 *, Range *);
void EffTableDrawTexBucket_1a0290(u8 *, s32, f32);
void EffTableFreeIndex_1a0470(u8 *);
}

extern "C" void MenuMobPreviewDraw_35fa50(Self *self)
{
    Range r;
    u8 *g;
    s32 y;
    s32 t;
    s32 i;
    s32 hi;

    if (self->model == 0) {
        return;
    }
    if (D_004823D4 == 0) {
        return;
    }
    g = GetDrawCtx_15de80();
    DrawEnvPush_144830(g);
    t = *(s32 *)(g + 0x270);
    y = 0x146;
    if (self->mode == 4) {
        y += 0x28;
    }
    DrawEnvSetScissor_157580(t, 0x69, 0x64, 0x1D5, y);
    DrawListAddEnv_1421d0(g);
    DrawListAddTexLoad_1418c0(GetDrawCtx_15de80(), 1.0f, 0x209);
    CameraSetViewFromCameraBase_142dd0(GetDrawCtx_15de80(), D_004823D4);
    DrawListAddCameraMatrixPacket_1481b0(GetDrawCtx_15de80());
    DrawListAddViewPacket_1482e0(GetDrawCtx_15de80());
    if (self->mode == 3 && self->flag244 == 0) {
        Character2DrawTintedMaybe_1ae620(self->model, 12.0f, 12.0f, 12.0f, 1.0f);
    } else {
        self->model->v24();
    }
    memset(&r, 0, 8);
    EffTableBuildIndexMaybe_1a04d0(self->list, &r);
    hi = r.hi;
    for (i = r.lo; i <= hi; i++) {
        DrawListAddTexLoad_1418c0(g, 1.0f, i);
        EffTableDrawTexBucket_1a0290(self->list, i, 1.0f);
    }
    EffTableFreeIndex_1a0470(self->list);
    DrawEnvPop_144800(g);
    DrawListAddEnv_1421d0(g);
}
