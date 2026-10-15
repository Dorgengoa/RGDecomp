#include "types.h"

typedef struct S00268f10 {
    u8 pad0[0x4DC];
    s32 unk4DC;
} S00268f10;

typedef struct P00268f10 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x10];
    u8 *unk2C;
    s32 unk30;
    u8 pad34[4];
    u8 *unk38;
    s32 unk3C;
    u8 unk40[0x20];
    u8 unk60[0x20];
    u8 pad80[8];
} P00268f10;

extern void Sprintf_1343b8(void *arg0, void *arg1, s32 arg2);
extern u8 *GetDrawCtxNameTable_15de40(void);
extern void InfoCfgParseAll_1afd00(void *arg0, P00268f10 *arg1);
extern s32 RecStackGetSlot_1c4330(s32 arg0, s32 arg1);
extern S00268f10 *ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern void memset(void *dst, s32 val, s32 n);
extern void strcpy(void *dst, void *src);
extern u8 D_0045EF98[0x400];
extern s32 D_00481F78;
extern s32 D_004BD980[];

s32 EvSceneObjReloadCfg_268f10(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 name[0x20];
    P00268f10 prm;
    s32 h;
    s32 v;
    u8 *w;
    S00268f10 *obj;

    h = RecStackGetSlot_1c4330(D_00481F78, D_004BD980[arg0]);
    if (arg2 < 0 || arg2 - 0x40 >= 0x40) {
        return 0;
    }
    if ((obj = ObjRecGetLiveObject_1c4a90(D_00481F78, arg2)) == NULL) {
        return 0;
    }
    v = obj->unk4DC;
    if (v < 0) {
        return 0;
    }
    Sprintf_1343b8(name, D_0045EF98, arg2);
    w = GetDrawCtxNameTable_15de40();
    if (arg2 >= 0x40) {
        strcpy(w + 0x1E4, name);
    }
    memset(&prm, 0, 0x88);
    prm.unk2C = prm.unk40;
    prm.unk30 = 8;
    prm.unk38 = prm.unk60;
    prm.unk3C = 8;
    prm.unk0 = arg3;
    prm.unk4 = arg1;
    prm.unk14 = v;
    prm.unk8 = h;
    prm.unkC = h;
    prm.unk10 = h;
    prm.unk18 = 0;
    InfoCfgParseAll_1afd00(obj, &prm);
    if (arg2 >= 0x40) {
        w[0x1E4] = 0;
    }
    return 1;
}
