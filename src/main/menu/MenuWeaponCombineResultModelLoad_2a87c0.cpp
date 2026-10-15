#include "types.h"
extern "C" {
extern void MemStackAlign64_14d8e0(void *);
extern void *MemStackNew_14e230(s32, void *);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void InfoCfgParseAll_1afd00(void *, void *);
extern void ModelObjExCtor_1c4920(void *);
extern void LoaderQueueAppendSeparator_1cd670(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void GetGameData_1fede0(void);
extern void ReturnZero_207fe0(void);
extern void LoadHandleArrayReset_28b160(void *, s32);
extern s32 LoadHandleIsPending_28b210(void *);
extern s32 LoadHandleGetId_28b220(void *);
extern void LoadHandleFree_28b230(void *);
extern s32 LoadHandleGetData_28b270(void *, void *);
extern s32 LoadHandleGetStatus_28b2e0(void *);
extern void LoadHandleRequestFile_28b550(void *, void *, s32, s32);
extern void MenuItemTempRBufInit_2a8a20(void);
extern void *memset(void *, s32, u32);

extern u8 D_00461448[0x400];
extern u8 D_00461460[0x400];
extern u8 D_00470F50[0x400];
extern u8 D_004DB3D0[0x400];
extern u8 D_004DB520[0x400];
}

class Obj {
public:
    u8 pad[0x1B0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void g();
    virtual void d19();
    virtual void d20();
    virtual void f();
};

extern "C" {
extern Obj *D_004824B8;
extern u8 D_00482494;
}

struct Req {
    s32 id;
    void *p4;
    void *p8;
    void *pC;
    void *p10;
    s32 x14;
    s32 x18;
    u8 pad1C[0x10];
    void *x2C;
    s32 x30;
    u8 pad34[4];
    void *x38;
    s32 x3C;
    u8 b40[0x20];
    u8 b60[0x28];
    u8 pad88[0x10];
};

extern "C" s32 MenuWeaponCombineResultModelLoad_2a87c0(s32 arg0) {
    Req req;
    s32 out;
    s32 id;
    Obj *o;

    if (arg0 != 0) {
        GetGameData_1fede0();
        MenuItemTempRBufInit_2a8a20();
        LoadHandleArrayReset_28b160(D_004DB520, 1);
        LoadHandleRequestFile_28b550(D_004DB520, D_00461460, 0, 0);
        LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
        D_004824B8 = 0;
        D_00482494 = 0;
    }
    if (D_004824B8 != NULL) {
        return 1;
    }
    if (LoadHandleGetId_28b220(D_004DB520) == -1) {
        return 0;
    }
    if (LoadHandleIsPending_28b210(D_004DB520) == 0) {
        return 0;
    }
    if (LoadHandleGetStatus_28b2e0(D_004DB520) == 1) {
        id = LoadHandleGetData_28b270(D_004DB520, &out);
        MemStackAlign64_14d8e0(D_004DB3D0);
        o = (Obj *)MemStackNew_14e230(0x790, D_004DB3D0);
        if (o != NULL) {
            ModelObjExCtor_1c4920(o);
            *(void **)((u8 *)o + 0x1B0) = D_00470F50;
        }
        D_004824B8 = o;
        if (o == NULL) {
            return 0;
        }
        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x209);
        memset(&req, 0, 0x88);
        req.x30 = 8;
        req.x2C = req.b40;
        req.x3C = 8;
        req.id = id;
        req.x38 = req.b60;
        req.p4 = D_00461448;
        req.p8 = D_004DB3D0;
        req.pC = D_004DB3D0;
        req.p10 = D_004DB3D0;
        req.x14 = 0x209;
        req.x18 = 1;
        D_004824B8->f();
        D_004824B8->g();
        InfoCfgParseAll_1afd00(D_004824B8, &req);
        D_00482494 = 0;
        LoadHandleFree_28b230(D_004DB520);
        ReturnZero_207fe0();
        return 1;
    }
    return 0;
}
