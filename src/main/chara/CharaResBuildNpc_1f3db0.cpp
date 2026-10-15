#include "types.h"
//PRAGMA

struct ObjData {
    u8 pad0[0x1B0];
    void *vt;
    u8 pad1B4[0x5DC];
};

struct VBase {
    u8 pad0[0x1B0];
};

class VObj : public VBase {
public:
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
    virtual void v44(f32);
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void v58();
    virtual void v5C();
};

struct Rec {
    s16 x0;
    u8 pad2[2];
    s16 x4;
    u8 x6;
    u8 pad7;
    ObjData *x8;
    char name[0x58];
    s16 x64;
};

struct Ent {
    u8 pad0[0x6C];
    s16 x6C;
};

struct Info {
    u8 pad0[0x2C];
    s32 x2C;
};

extern "C" {
s32 GetCharaDataMgr_1fdb70(void);
s32 CharaDataGetLoadState_1ed5a0(s32, s32);
s32 CharaDataGetNodeModel_1ed540(s32, s32, s32);
s32 RecStackPush_1c4240(s32, s32);
Info *RecStackGetSlot_1c4330(s32, s32);
void ModelObjExCtor_1c4920(ObjData *);
void Character2ResetMaybe_1aef80(ObjData *);
void ModelObjExCopy_1aff40(s32, ObjData *, void *);
void RecStackPop_1c4140(s32, s32);
void *MemStackHeapAllocFront_14dd10(s32, s32);
void MemStackClear_14dff0(char *);
void MemStackInit_14d810(char *, void *, s32);
u32 strlen(const char *);
char *strcpy(char *, const char *);
ObjData *MemStackNew_14e230(s32, char *);
void GameSceneObjBindMaybe_1cfcd0(s32, s32, ObjData *, s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
void ParamTableSetAlpha_1cfb10(s32, s32, f32);
void ParamTableFadeToOne_1cf9e0(s32, s32, s32);
void ModelObjPlayMotionByName_1867a0(ObjData *, char *, s32);
Ent *CharaDataFindById_1ed990(s32, s32);

extern char D_0045B890[];
extern char D_0045B8B0[];
extern u8 D_00470F50[];
}

extern "C" void CharaResBuildNpc_1f3db0(Rec *rec, s32 arg1, s32 arg2)
{
    //DECLS
    ObjData local;
    s32 mgr;
    s32 h;
    Info *info;
    void *buf;
    s32 key;
    Ent *e;
    s32 tmp;
    ObjData *obj;
    s32 len;
    s32 v;
    //ENDDECLS

    mgr = GetCharaDataMgr_1fdb70();
    v = CharaDataGetLoadState_1ed5a0(mgr, rec->x4);
    if (v == 2) {
        return;
    }
    if (v == 4) {
        rec->x64 = 4;
        return;
    }
    if ((h = CharaDataGetNodeModel_1ed540(mgr, rec->x4, 0)) == 0) {
        goto fail;
    }
    {
        rec->x8 = 0;
        key = RecStackPush_1c4240(arg1, 0);
        info = RecStackGetSlot_1c4330(arg1, key);
        if (info == 0) {
            rec->x64 = 4;
            return;
        }
        ModelObjExCtor_1c4920(&local);
        local.vt = D_00470F50;
        Character2ResetMaybe_1aef80(&local);
        ModelObjExCopy_1aff40(h, &local, info);
        len = info->x2C + 0x7A;
        ((VObj *)&local)->v58();
        RecStackPop_1c4140(arg1, key);
        buf = MemStackHeapAllocFront_14dd10(arg2, len);
        if (buf == 0) {
            MemStackClear_14dff0(rec->name);
            rec->x64 = 4;
            return;
        }
        MemStackClear_14dff0(rec->name);
        MemStackInit_14d810(rec->name, buf, len);
        if (strlen(D_0045B8B0) < 0x10) {
            strcpy(rec->name, D_0045B8B0);
        }
        obj = MemStackNew_14e230(0x790, rec->name);
        if (obj != 0) {
            ModelObjExCtor_1c4920(obj);
            obj->vt = D_00470F50;
        }
        rec->x8 = obj;
        ((VObj *)obj)->v5C();
        ModelObjExCopy_1aff40(h, rec->x8, rec->name);
        GameSceneObjBindMaybe_1cfcd0(arg1, rec->x0, rec->x8, 0);
        ObjRecSetFlag2_1c3e80(arg1, 1, rec->x0);
        ParamTableSetAlpha_1cfb10(arg1, rec->x0, 0.0f);
        ParamTableFadeToOne_1cf9e0(arg1, rec->x0, 0xF);
        ModelObjPlayMotionByName_1867a0(rec->x8, D_0045B890, 0);
        ((VObj *)rec->x8)->v44(0.0f);
        rec->x6 |= 1;
        e = CharaDataFindById_1ed990(mgr, rec->x4);
        if (e != 0) {
            e->x6C++;
        }
    }
fail:
    rec->x6 |= 0x80;
    rec->x64 = 3;
}
