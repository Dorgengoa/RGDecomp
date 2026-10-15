#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  vptr at offset 0 of the object; the
   slot's byte offset is 8 + 4*index because mwcc's vtable has two leading
   words, so the 0x70 slot is virtual #26. */

struct Rec { u8 pad00[0x8]; s16 *f8; };
struct CMgr {
    virtual Rec *v0(s32);
    virtual Rec *v1(s32);
    virtual Rec *v2(s32);
    virtual Rec *v3(s32);
    virtual Rec *v4(s32);
    virtual Rec *v5(s32);
    virtual Rec *v6(s32);
    virtual Rec *v7(s32);
    virtual Rec *v8(s32);
    virtual Rec *v9(s32);
    virtual Rec *v10(s32);
    virtual Rec *v11(s32);
    virtual Rec *v12(s32);
    virtual Rec *v13(s32);
    virtual Rec *v14(s32);
    virtual Rec *v15(s32);
    virtual Rec *v16(s32);
    virtual Rec *v17(s32);
    virtual Rec *v18(s32);
    virtual Rec *v19(s32);
    virtual Rec *v20(s32);
    virtual Rec *v21(s32);
    virtual Rec *v22(s32);
    virtual Rec *v23(s32);
    virtual Rec *v24(s32);
    virtual Rec *v25(s32);
    virtual Rec *v26(s32);
};

struct Slot { u32 lo, hi; };
struct Sys { u8 pad00[0xC]; void *fC; };
struct World { u8 pad00[0x60]; Sys *f60; };
struct Reg { u8 pad00[0x14]; void *f14; };
struct Hit { u8 pad00[0xC]; void *fC; };
struct EventContext { void *arg; void *player; };
extern EventContext *gEventContext;

extern "C" void *GetCharaResMgr_1fdb60(void);
extern "C" Reg *GetGameData_1fede0(void);
extern "C" World *GetWorldDataMgr_1fedf0(void);
extern "C" s32 ScriptGetInt_2490f0(Slot *);
extern "C" Hit *CharaMgrPoolFindByDataId_3a8a70(void *, s32, s32, s32, s32, s32, s32);
extern "C" void CharaResReleaseById_1f1160(void *, void *, void *);
extern "C" void CharaResReleaseCharaDataWithTexIds_1f0fb0(void *, s32);

extern "C" s32 EvCmdCharaResRelease_243dd0(Slot *args)
{
    void *ctxArg;
    void *ui;
    Reg *g;
    World *w;
    s32 id;
    Hit *h;
    void *mgr;
    Rec *r;
    s16 *s;

    ctxArg = gEventContext->arg;
    ui = GetCharaResMgr_1fdb60();
    g = GetGameData_1fede0();
    w = GetWorldDataMgr_1fedf0();
    id = ScriptGetInt_2490f0(args);
    h = CharaMgrPoolFindByDataId_3a8a70(g->f14, id, 1, 1, 0, 0, 0);
    if (h == 0) {
        return 0;
    }
    mgr = w->f60->fC;
    r = ((CMgr *)mgr)->v26((s16)id);
    if (r == 0) {
        return 0;
    }
    s = r->f8;
    if (s == 0) {
        return 0;
    }
    CharaResReleaseById_1f1160(ui, ctxArg, h->fC);
    CharaResReleaseCharaDataWithTexIds_1f0fb0(ui, *s);
    return 1;
}
