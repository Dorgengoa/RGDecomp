#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  vptr at offset 0 of the object; the
   slot's byte offset is 8 + 4*index because mwcc's vtable has two leading
   words, so the 0x70 slot is virtual #26. */

struct Rec { u8 pad00[0x20]; s16 *f20; };
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

struct Sys { u8 pad00[0xC]; void *fC; };
struct World { u8 pad00[0x64]; Sys *f64; };
struct Reg { u8 pad00[0x1C]; void *f1C; };
struct Hit { u8 pad00[0xC]; void *fC; };

extern "C" World *GetWorldDataMgr_1fedf0(void);
extern "C" Reg *GetGameData_1fede0(void);
extern "C" void *GetCharaDataMgr_1fdb70(void);
extern "C" Hit *ObjMgrFindFiltered_3bb190(void *, s32, s32, s32, s32, s32, s32, s32);
extern "C" void CharaUnloadById_2f3090(void *, s32);
extern "C" void CharaDataReleaseById_1ed850(void *, s32);

extern "C" void CharaReleaseAllById_2f2ed0(s32 id)
{
    World *w;
    Reg *g;
    void *ui;
    Hit *h;
    void *mgr;
    Rec *r;
    s16 *t;

    w = GetWorldDataMgr_1fedf0();
    g = GetGameData_1fede0();
    ui = GetCharaDataMgr_1fdb70();
    /* retail's loop is UN-ROTATED: test at the TOP, backward b at the
       bottom.  A plain `while` gets rotated; `for (;;) { if (!c) break; }`
       does not. */
    for (;;) {
        h = ObjMgrFindFiltered_3bb190(g->f1C, id, 1, 1, 0, 0, 0, 0);
        if (h == 0) {
            break;
        }
        CharaUnloadById_2f3090(h->fC, 1);
    }
    mgr = w->f64->fC;
    r = ((CMgr *)mgr)->v26((s16)id);
    if (r != 0) {
        t = r->f20;
        if (t != 0) {
            CharaDataReleaseById_1ed850(ui, *t);
        }
    }
}
