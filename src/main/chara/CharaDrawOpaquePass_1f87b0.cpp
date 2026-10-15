#pragma opt_lifetimes off
#include "types.h"

struct Pad1B0 { u8 pad[0x1B0]; };
class Obj : public Pad1B0 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(f32);
};

extern "C" {
void *GetCurrentScene_1f5be0(void);
void *GetDrawCtx_15de80(void);
void GetGameData_1fede0(void);
void GetMapMgr_201a90(void);
void GameSceneCBlurClearMaybe_1cf830(void *);
s32 ObjRecIsDrawableMaybe_1c48b0(void *, s32);
s32 ObjRecGetValue_1c3d30(void *, s32, s32);
u8 *ObjRecGetLiveObject_1c4a90(void *, s32);
u8 *ParamTableGetRec_1cfbc0(void *, s32);
s32 ObjGetNthAttachPointPosSafe_23b0c0(void *, s32, s32, void *);
void *ModelGetRootFrame_1511a0(void *);
void FrameGetWorldPos_148f30(void *, void *);
u32 ObjRecGetFlags_1c3d90(void *, s32, s32);
void DrawListAddTexLoad_1418c0(void *, s32, f32);
void Character2LightBlendStep_1ae820(void *);
void *ActionMgrFindById_233b50(void *, s32);
s32 EventObjMgrIsRunning_27af20(void);
void CharaGetTintColor_213fe0(void *, void *);
f32 CharaGetTintLevel_213ff0(void *);
void Character2DrawTintedMaybe_1ae620(void *, f32, f32, f32, f32);
void ObjRecClearFlags_1c3dc0(void *, s32, s32, s32);
extern s32 D_00481A7C;
extern u8 D_004B8680[];
}

static inline s32 slotOf(s32 i)
{
    if (i < 12) return -1;
    if (i < 60) return (i - 12) >> 2;
    return -1;
}

#define SLOT(x) (((x) >= 12 && (x) < 60) ? (((x) - 12) >> 2) : -1)
#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" void CharaDrawOpaquePass_1f87b0(void)
{
    s16 ids[224];
    f32 vals[224];
    u8 mtx[16];
    f32 vec[4];
    void *a;
    void *b;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    u8 *tbl;
    u8 *obj;
    u8 *p;
    s32 r;
    s32 idx;
    s32 id;
    Obj *o;
    void *e;
    s32 arg;

    a = GetCurrentScene_1f5be0();
    b = GetDrawCtx_15de80();
    GetGameData_1fede0();
    GetMapMgr_201a90();
    tbl = D_004B8680;
    GameSceneCBlurClearMaybe_1cf830(a);
    n = 0;
    for (i = 0; i < 224; i++) {
        if (ObjRecIsDrawableMaybe_1c48b0(a, i) == 0) continue;
        r = ObjRecGetValue_1c3d30(a, 1, i);
        if (r == 4 || r == 7 || r == 9) continue;
        obj = ObjRecGetLiveObject_1c4a90(a, i);
        if (obj == 0) continue;
        idx = i;
        if (i >= 12 && i < 60) idx = SLOT(i);
        p = ParamTableGetRec_1cfbc0(a, i);
        if (p == 0) continue;
        if (ObjGetNthAttachPointPosSafe_23b0c0(obj, 0, 0, mtx) == 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(obj), mtx);
        }
        if (*(f32 *)(obj + 0x448) < 1.0f) continue;
        if (ObjRecGetFlags_1c3d90(a, 1, idx) & 0x1000) continue;
        if (*(f32 *)(obj + 0x448) < 1.0f) continue;
        ids[n] = i;
        vals[n] = *(f32 *)(p + 0xC);
        n++;
    }
    for (j = 1; j < n; j++) {
        for (k = 0; k < j; k++) {
            if (vals[k] < vals[j]) {
                f32 t = vals[k];
                vals[k] = vals[j];
                vals[j] = t;
                t = ids[k];
                ids[k] = ids[j];
                ids[j] = t;
            }
        }
    }
    for (i = 0; i < n; i++) {
        id = ids[i];
        o = (Obj *)ObjRecGetLiveObject_1c4a90(a, id);
        ParamTableGetRec_1cfbc0(a, id);
        DrawListAddTexLoad_1418c0(b, *(s32 *)((u8 *)o + 0x4DC), 1.0f);
        o->v4(1.0f);
        Character2LightBlendStep_1ae820(o);
        arg = id;
        if (id >= 12 && id < 60) arg = SLOT(id);
        e = ActionMgrFindById_233b50(tbl, arg);
        ZERO(vec, 16);
        if (e != 0 && EventObjMgrIsRunning_27af20() != 0) {
            CharaGetTintColor_213fe0(e, vec);
            vec[3] = CharaGetTintLevel_213ff0(e);
        }
        if (D_00481A7C > 0) {
            *(s32 *)((u8 *)o + 0x450) = 0;
        } else {
            *(s32 *)((u8 *)o + 0x450) = 1;
        }
        Character2DrawTintedMaybe_1ae620(o, vec[0], vec[1], vec[2], vec[3]);
        ObjRecClearFlags_1c3dc0(a, 1, id, 0x40000);
    }
}
