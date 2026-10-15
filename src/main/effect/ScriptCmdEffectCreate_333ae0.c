#include "types.h"

typedef struct { u16 x : 16; } H;
typedef union { u32 w; struct { H lo; H hi; } f; } Bits;

typedef struct R {
    s16 a;
    s32 b;
    s32 c;
    Bits p;
    s32 f;
} R;

s32 GetEffectMgr_2d9040();
void EffectSetHandle_2dd3e0(s32, R *);
void EffectCreateByName_2e1020(R *, s32, s32, s16);
void ScriptSlotStoreIntRef_3347f0(s32, s32);
s32 ScriptSlotGetCodeAddr_334870(s32);
s32 ScriptSlotGetInt_3348b0(s32);
extern s32 D_004826E0;

s32 ScriptCmdEffectCreate_333ae0(s32 arg0, s32 arg1) {
    R t;
    R r;
    s32 v;
    s32 w;
    s32 saved;

    if (arg1 < 2) {
        return 0;
    }
    t.p.w = 0;
    v = ScriptSlotGetCodeAddr_334870(arg0 + 8);
    w = -1;
    if (arg1 > 2) {
        w = ScriptSlotGetInt_3348b0(arg0 + 0x10);
    }
    arg1 = D_004826E0;
    EffectCreateByName_2e1020(&r, GetEffectMgr_2d9040(), v, w);
    t.a = r.a;
    t.b = r.b;
    t.c = r.c;
    t.p.w = r.p.w;
    t.p.f.lo = r.p.f.lo;
    t.p.f.hi = r.p.f.hi;
    t.f = r.f;
    D_004826E0 = arg1;
    EffectSetHandle_2dd3e0(arg1, &t);
    ScriptSlotStoreIntRef_3347f0(arg0, t.b);
    return 1;
}
