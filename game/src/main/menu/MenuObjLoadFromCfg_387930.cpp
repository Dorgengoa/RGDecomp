/* rgp:protos */
#line 1
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
extern s8 * MenuObjInsectGetInsectorParam_386d90(s8 *, int, int, int);
extern s8 *MenuObjInsectGetItemDef_386dc0(s8 *);
extern void MenuObjSetLightRecMaybe_387cf0(s8 *, s32);
extern void MenuObjReset_387dc0(void *);
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void setScale(f32 a0) { VCM(void, (void *, f32), 0x44, a0); }
    
    
    
    
    
    void reset() { VCM0(void, 0x5C); }
};

struct Handler {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 getId() { return VCM0(s32, 0x128); }
};

extern "C" void MenuObjLoadFromCfg_387930(Obj *self, s32 arg1, s32 arg2, s32 arg3, Handler *arg4) {
    s8 *arg0 = (s8 *)self;
    char name[8];
    Req req __attribute__((aligned(16)));
    s8 *w;
    s8 *e;
    s8 *f;
    s32 id;

    MenuObjReset_387dc0((void *)self);
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
    f = MenuObjInsectGetInsectorParam_386d90(arg0, 0, 0, 0);
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
    *(s32 *)(arg0 + 0x964) = ConstructNewArray_100710(MemStackNew_14e1b0(0x610, arg3), (void *)MenuObjRouteNodeCtor_387c10, 0, 0x30, 0x20);
    *(s32 *)(arg0 + 0x960) = 0x20;
    ModelSetDesignVisible_391860(arg0, e, *(s16 *)(f + 8));
    MenuObjSetLightRecMaybe_387cf0(arg0, MapDataGetModel_1e7810(MapMgrGetAuxAreaFwd_389e40()));
    *(arg0 + 0x985) = 1;
}
