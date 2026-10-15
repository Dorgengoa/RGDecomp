#include "types.h"

typedef struct {
    s32 kind;
    void *fmt;
    s32 a;
    s32 b;
    s32 c;
    s32 arg;
    s32 one;
    u8 pad1c[0x2C - 0x1C];
    u8 *p1;
    s32 n1;
    u8 pad34[4];
    u8 *p2;
    s32 n2;
    u8 buf1[0x20];
    u8 buf2[0x28];
    u8 tail[0x10];
} Req;


extern "C" {
extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern void Sprintf_1343b8(char *, void *, s32);
extern f32 RandFloat_13c010(void);
extern void MemStackReset_14d830(s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern s8 *GetDrawCtxNameTable_15de40(void);
extern void ModelObjPlayMotionByName_1867a0(s8 *, s8 *, s32);
extern void ModelObjSetCBlurTexMaybe_1ad5d0(s8 *, s32);
extern void InfoCfgParseAll_1afd00(s8 *, Req *);
extern s32 GameSceneCBlurFindTex_1cf7d0(s32);
extern s32 MapDataGetModel_1e7810(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern void *MenuObjParamsFindById_3867c0(s32);
extern s8 *MenuObjInsectGetInsectorParam_386d90(s8 *);
extern s8 *MenuObjInsectGetItemDef_386dc0(s8 *);
extern void MenuObjSetLightRecMaybe_387cf0(s8 *, s32);
extern void MenuObjReset_387dc0(void);
extern void MenuObjParamsRollCountMaybe_387ef0(s8 *);
extern void MenuObjParamsRollTime_387f60(s8 *);
extern s32 MapMgrGetAuxAreaFwd_389e40(void);
extern void InsectModelApplyColorRec_3913f0(s8 *, s32, s32);
extern void ModelSetDesignVisible_391860(s8 *, s8 *, s16);
extern void *memcpy(void *, const void *, u32);
extern void *memset(void *, s32, u32);
extern char *strcpy(char *, const char *);
extern u8 D_00463EC8[];
extern char D_00463F18[];
extern u8 D_00463F30[];
extern s32 D_004833FC;
extern u8 D_004E9280[];
extern void MenuObjRouteNodeCtor_387c10(void);

}

struct ObjBase {
    u8 pad[0x1B0];
};

struct Obj : ObjBase {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void setScale(f32);
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void reset();
};

struct Handler {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual s32 getId();
};

extern "C" void MenuObjLoadFromCfg_387930(Obj *self, s32 arg1, s32 arg2, s32 arg3, Handler *arg4) {
    s8 *arg0 = (s8 *)self;
    char name[8];
    Req req;
    s8 *w;
    s8 *e;
    s8 *f;
    s32 id;

    MenuObjReset_387dc0();
    if (arg3 == 0 || arg1 == 0 || arg4 == NULL) {
        return;
    }
    MemStackReset_14d830(arg3);
    Sprintf_1343b8(name, D_00463F30, D_004833FC);
    if (++D_004833FC > 9999) {
        D_004833FC = 0;
    }
    w = GetDrawCtxNameTable_15de40();
    strcpy((char *)(w + 0x1E4), name);
    *(Handler **)(arg0 + 0x96C) = arg4;
    memset(&req, 0, 0x88);
    req.p1 = req.buf1;
    req.kind = arg1;
    req.p2 = req.buf2;
    req.arg = arg2;
    req.n1 = 8;
    req.fmt = D_00463EC8;
    req.n2 = 8;
    req.one = 1;
    req.a = arg3;
    req.b = arg3;
    req.c = arg3;
    self->reset();
    InfoCfgParseAll_1afd00(arg0, &req);
    ModelObjSetCBlurTexMaybe_1ad5d0(arg0, GameSceneCBlurFindTex_1cf7d0(GetCurrentScene_1f5be0()));
    *(w + 0x1E4) = 0;
    *(arg0 + 0x984) = 0;
    e = MenuObjInsectGetItemDef_386dc0(arg0);
    f = MenuObjInsectGetInsectorParam_386d90(arg0);
    *(s32 *)(arg0 + 0x970) = 0x7D7;
    if (e != NULL) {
        id = *(s16 *)(e + 4);
        *(s32 *)(arg0 + 0x970) = id;
        switch (id) {
        case 0x7D7:
        case 0x7D8:
        case 0x7D9:
            *(arg0 + 0x984) = 1;
            break;
        }
    }
    strcpy((char *)(arg0 + 0x974), D_00463F18);
    if (f != NULL) {
        *(arg0 + 0x979) = *(s16 *)(f + 8) + 0x31;
    }
    ModelObjPlayMotionByName_1867a0(arg0, arg0 + 0x974, 0);
    self->setScale(12.0f * RandFloat_13c010());
    InsectModelApplyColorRec_3913f0(arg0, *(s32 *)(arg0 + 0x970), arg4->getId());
    *(void **)(arg0 + 0x98C) = MenuObjParamsFindById_3867c0(*(s32 *)(arg0 + 0x970));
    if (*(void **)(arg0 + 0x98C) == NULL) {
        *(void **)(arg0 + 0x98C) = D_004E9280;
    }
    memcpy(arg0 + 0x990, *(void **)(arg0 + 0x98C), 0x34);
    MenuObjParamsRollTime_387f60(arg0 + 0x990);
    MenuObjParamsRollCountMaybe_387ef0(arg0 + 0x990);
    *(s32 *)(arg0 + 0x968) = 0;
    *(s32 *)(arg0 + 0x964) = ConstructNewArray_100710(MemStackNew_14e1b0(0x610, arg3), MenuObjRouteNodeCtor_387c10, 0, 0x30, 0x20);
    *(s32 *)(arg0 + 0x960) = 0x20;
    ModelSetDesignVisible_391860(arg0, e, *(s16 *)(f + 8));
    MenuObjSetLightRecMaybe_387cf0(arg0, MapDataGetModel_1e7810(MapMgrGetAuxAreaFwd_389e40()));
    *(arg0 + 0x985) = 1;
}
