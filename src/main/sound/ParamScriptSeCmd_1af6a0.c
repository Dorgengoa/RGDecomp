#include "types.h"

typedef struct E1af6a0 {
    f32 f0;
    f32 f4;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    s32 w10;
} E1af6a0;

extern s32 MemStackStrDup_14cff0(s32, s32);
extern s32 Strcasecmp_1345b8(s32, u8 *);
extern s32 SlotGetInt_15f720(s32);
extern f32 VariantGetFloat_15f740(s32);
extern s32 VariantGetInt_15f780(s32);
extern s32 MotionListFindSubEntry_172430(s32, s32, s32);
extern f32 NamedRecLerpMaybe_173980(s32, s32, f32);
extern s32 NamedRecFindIndex_173a00(s32, s32);
extern u8 D_0045A9A0[];
extern s32 D_0049D45C[4];
extern s32 D_0049D4E0[4];
extern s32 D_0049D4E4[4];
extern s32 D_0049D4E8[4];
extern s32 D_0049D4F8[4];
extern E1af6a0 *D_0049D4FC[4];
extern s32 D_0049D500[4];

s32 ParamScriptSeCmd_1af6a0(s64 *arg0, s32 argc)
{
    s32 sub;
    s32 s;
    s32 mgr;
    s32 h;
    s32 k;
    E1af6a0 *e;
    s32 type;
    f32 t;
    f32 v;
    s32 ref;
    s32 idx;
    s32 name;

    mgr = D_0049D4E0[0];
    if (mgr == 0) {
        return 0;
    }
    if (argc < 4) {
        return 0;
    }
    k = D_0049D45C[0];
    name = SlotGetInt_15f720((s32)arg0++);
    type = VariantGetInt_15f780((s32)arg0++);
    ref = 0;
    switch (type) {
    case 5:
        ref = MemStackStrDup_14cff0(SlotGetInt_15f720((s32)arg0++), k);
        sub = 1;
        break;
    default:
        sub = VariantGetInt_15f780((s32)arg0++);
        break;
    }
    t = VariantGetFloat_15f740((s32)arg0++);
    if (argc >= 5) {
        s = SlotGetInt_15f720((s32)arg0);
        if (type == 5 && s != 0 && Strcasecmp_1345b8(s, D_0045A9A0) == 0) {
            sub = 0;
        }
    }
    if (D_0049D500[0] >= D_0049D4F8[0]) {
        return 0;
    }
    e = &D_0049D4FC[0][D_0049D500[0]];
    h = MotionListFindSubEntry_172430(mgr + 0x1F0, D_0049D4E8[0], D_0049D4E4[0]);
    if (h == 0) {
        return 0;
    }
    idx = NamedRecFindIndex_173a00(h, name);
    if (idx < 0) {
        return 0;
    }
    if (t <= 1.0f) {
        v = NamedRecLerpMaybe_173980(h, idx, t);
    } else {
        v = t;
    }
    if (v <= 0.0f) {
        return 0;
    }
    e->f0 = v;
    e->f4 = 0.0f;
    e->hA = type;
    e->hC = sub;
    e->h8 = 0;
    e->hE = 0;
    e->w10 = ref;
    D_0049D500[0]++;
    return 1;
}
