#include "types.h"

class C2F3160 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual u8 *get(s16);
};

extern "C" {
extern s32 CharaCopyResSizeCheckMaybe_1efbe0(s32, s32, s64);
extern s32 CharaResRequestMon_1f29d0(s32, s32, s32, s64, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetActionMgr_1fdb50(void);
extern s32 GetCharaResMgr_1fdb60(void);
extern s32 GetNpcDataHeap_1fdd70(void);
extern u8 *GetGameData_1fede0(void);
extern u8 *GetWorldDataMgr_1fedf0(void);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void ActionMgrRemoveChara_233dc0(s32, s32);
extern s32 ActionMgrAddChara_23b2b0(s32, s16);
extern s32 GetEffectMgr_2d9040(void);
extern void EffectRequestByName_2e29d0(u8 *, s32, s32, s32, s32);
extern void ObjFreeRecursive_3bb4f0(s32, s32, s32);
extern s32 UnitDefCollectEffectRefsMaybe_4198f0(u8 *, u8 *, s32, u8 **, s32, s32);
}

extern "C" s32 UnitAddMonCharaMaybe_2f3160(s32 arg0, s64 arg1)
{
    u8 *spC0[0x20];
    u8 spB0[0x10];
    u8 *g;
    u8 *f;
    s32 h;
    s32 k;
    s32 w;
    s32 m;
    u8 *rec;
    s16 *id;
    s32 v;
    s32 n;
    s32 i;
    s32 t;

    if (arg0 < 0x80 || arg0 >= 0x9C) {
        return 0;
    }
    g = GetGameData_1fede0();
    f = GetWorldDataMgr_1fedf0();
    h = GetActionMgr_1fdb50();
    k = GetCharaResMgr_1fdb60();
    w = GetEffectMgr_2d9040();
    m = GetCurrentScene_1f5be0();
    rec = (*(C2F3160 **)(*(u8 **)(f + 0x64) + 0xC))->get(arg1);
    if (rec == 0) {
        return 0;
    }
    id = *(s16 **)(rec + 0x20);
    if (id == 0) {
        return 0;
    }
    if (CharaCopyResSizeCheckMaybe_1efbe0(k, m, arg1) < 0) {
        ObjFreeRecursive_3bb4f0(*(s32 *)(g + 0x1C), arg0, 1);
        return 0;
    }
    if (ActionMgrAddChara_23b2b0(arg0, *id) == 0) {
        ObjFreeRecursive_3bb4f0(*(s32 *)(g + 0x1C), arg0, 1);
        return 0;
    }
    t = CharaResRequestMon_1f29d0(k, m, arg0, arg1, 1);
    v = 0;
    if (t != 0) {
        v = ActionMgrFindById_233b50(h, arg0);
    }
    if (v == 0) {
        ObjFreeRecursive_3bb4f0(*(s32 *)(g + 0x1C), arg0, 1);
        ActionMgrRemoveChara_233dc0(h, arg0);
        return 0;
    }
    n = UnitDefCollectEffectRefsMaybe_4198f0(*(u8 **)(f + 0x64), rec, 1, spC0, 0x20, 0);
    for (i = 0; i < n; i++) {
        EffectRequestByName_2e29d0(spB0, w, GetNpcDataHeap_1fdd70(), *(s32 *)(spC0[i] + 0x8), *id);
    }
    return 1;
}
