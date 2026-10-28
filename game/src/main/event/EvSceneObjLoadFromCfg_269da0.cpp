/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK s17d try1: length 0x210 vs retail 0x214, 1 word short -- closest
   miss so far, worth a second look. */
#include "types.h"
#pragma opt_propagation off
#undef NULL
#define NULL 0
extern "C" {

typedef void (*VFunc5C)(void *);

extern s32 memset(void *, s32, s32);
extern s32 strcpy(void *, void *);
extern void Sprintf_1343b8(void *, void *, s32);
extern void *MemStackNew_14e230(s32, s32);
extern void NameTableFreeGroup_158ac0(void *, s32);
extern void * GetDrawCtxNameTable_15de40(void);
extern void InfoCfgParseAll_1afd00(void *, void *);
extern void ObjRecSetValue_1c3d60(s32, s32, s32, s32);
extern s32 RecStackGetSlot_1c4330(s32, s32);
extern void ModelObjExCtor_1c4920(void *, int, int, int);
extern void *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void GameSceneObjBindMaybe_1cfcd0(s32, s32, void *, s32);
extern s32 GetEffectMgr_2d9040(void);
extern u8 D_0045EF98[0x400];
extern u8 D_0045F1B0[0x400];
extern u8 D_00470F50[0x400];
extern s32 D_0047E180;
extern s32 D_00481F78;
extern s32 D_004BD980[];

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x5C); }
};
s32 EvSceneObjLoadFromCfg_269da0(s32 arg0, s32 pd1, s32 arg2, s32 arg3)
{
    u8 sp100[32] __attribute__((aligned(16)));
    u8 sp70[0x90] __attribute__((aligned(16)));
    s32 slot;
    s32 id;
    u32 tag;
    u8 *obj;
    u8 *e2;
    s32 next;

    id = RecStackGetSlot_1c4330(D_00481F78, D_004BD980[arg0]);
    if ((arg2 < 0) || (arg2 - 0x40 >= 0x40)) return 0;
    tag = arg2 + 0x1C9;
    obj = (u8 *)GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(obj, tag);
    Sprintf_1343b8(sp100, D_0045EF98, arg2);
    if (arg2 >= 0x40 && arg2 < 0x80) {
        strcpy(obj + 0x1E4, sp100);
    }
    e2 = (u8 *)MemStackNew_14e230(0x790, id);
    if (e2 != NULL) {
        ModelObjExCtor_1c4920(e2, 0, 0, 0);
        *(u8 **)(e2 + 0x1B0) = D_00470F50;
    }
    if (e2 == NULL) {
        return 0;
    }

    memset(sp70, 0, 0x88);
    *(u8 **)(sp70 + 0x2C) = sp70 + 0x40;
    *(s32 *)(sp70 + 0x30) = 8;
    *(s32 *)(sp70 + 0x3C) = 8;
    *(u8 **)(sp70 + 0x38) = sp70 + 0x60;
    *(s32 *)(sp70 + 0x0) = arg3;
    *(u8 **)(sp70 + 0x4) = &(*(u8 *)D_0045F1B0);
    *(s32 *)(sp70 + 0x18) = 1;
    *(s32 *)(sp70 + 0x8) = id;
    *(s32 *)(sp70 + 0xC) = id;
    *(s32 *)(sp70 + 0x10) = id;
    *(s32 *)(sp70 + 0x14) = tag;

    ((VC_0 *)(e2))->f();
    next = GetEffectMgr_2d9040() + 0x58;
    *(s32 *)(e2 + 0x53C) = next;
    if (next != 0) {
        s32 t = D_0047E180;
        D_0047E180 = t + 1;
        *(s32 *)(e2 + 0x538) = t;
    }
    InfoCfgParseAll_1afd00(e2, sp70);
    GameSceneObjBindMaybe_1cfcd0(D_00481F78, arg2, e2, 0);
    *(s32 *)(e2 + 0x4DC) = tag;
    {
        u8 *slotp = (u8 *)ObjRecGetLiveObject_1c4a90(D_00481F78, arg2);
        if (slotp != NULL) {
            *(s32 *)(slotp + 0x1D4) = 0x447A0000;
            *(s32 *)(slotp + 0x1D8) = 0x41F00000;
        }
    }
    if (arg2 >= 0x40 && arg2 < 0x80) {
        *(u8 *)(obj + 0x1E4) = 0;
    }
    ObjRecSetValue_1c3d60(D_00481F78, 1, arg2, 2);
    return 1;
}

}
