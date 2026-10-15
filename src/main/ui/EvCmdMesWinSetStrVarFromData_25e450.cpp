#include "types.h"

/* jalr $25 == a C++ VIRTUAL call.  vptr at offset 0 of the object; the
   slot's byte offset is 8 + 4*index because mwcc's vtable has two leading
   words, so the 0x70 slot is virtual #26. */

struct Rec { u8 pad00[0xC]; s32 fC; s32 f10; };
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
struct Sys { u8 pad00[0x8]; void *f8; };
struct World { u8 pad00[0x40]; Sys *f40; };

extern "C" World *GetWorldDataMgr_1fedf0(void);
extern "C" s32 ScriptGetInt_26a2a0(Slot *);
extern "C" void *MesMgrGetSlotWin_266af0(s32);
extern "C" void MesWinSetStrVar_276a00(void *, s32, s32);

extern "C" s32 EvCmdMesWinSetStrVarFromData_25e450(Slot *args, s32 argc)
{
    void *h;
    s32 a;
    s32 id;
    void *mgr;
    Rec *r;
    s32 m;

    h = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0(args++));
    if (h == 0) {
        return 0;
    }
    a = ScriptGetInt_26a2a0(args++);
    id = ScriptGetInt_26a2a0(args++);
    mgr = GetWorldDataMgr_1fedf0()->f40->f8;
    r = ((CMgr *)mgr)->v26((s16)id);
    if (r == 0) {
        return 0;
    }
    m = 0;
    if (argc >= 4) {
        m = ScriptGetInt_26a2a0(args);
    }
    if (m == 0) {
        MesWinSetStrVar_276a00(h, a - 1, r->fC);
    } else if (m == 1) {
        MesWinSetStrVar_276a00(h, a - 1, r->f10);
    }
    return 1;
}
