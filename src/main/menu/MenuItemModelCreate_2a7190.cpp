#include "types.h"

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct {
    s32 unk0;
    u8 *unk4;
    u8 *unk8;
    u8 *unkC;
    u8 *unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x2C - 0x1C];
    u8 *unk2C;
    s32 unk30;
    u8 pad34[0x38 - 0x34];
    u8 *unk38;
    s32 unk3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
} Params;

class Obj {
public:
    u8 pad[0x1B0];
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3C();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4C();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5C();
};

extern "C" {
void MemStackAlign64_14d8e0(void *);
Obj *MemStackNew_14e230(s32, void *);
void ModelSetScale_150ff0(Obj *, Vec4 *);
void ModelSetRot_151080(Obj *, Vec4 *);
void ModelSetPos_151110(Obj *, Vec4 *);
void NameTableFreeGroup_158ac0(s32, s32);
s32 GetDrawCtxNameTable_15de40(void);
void InfoCfgParseAll_1afd00(Obj *, Params *);
void ModelObjExCtor_1c4920(Obj *);
void *memset(void *, s32, u32);
extern u8 D_00461448[];
extern u8 D_00470F50[];
extern u8 D_004DB3D0[];
extern Obj *D_004824BC;
extern f32 D_0047EC40;
extern f32 D_0047EC44;
extern f32 D_0047EC48;
extern f32 D_0047EC4C;
extern f32 D_0047D5B0;
extern f32 D_0047D278;
}

extern "C" void MenuItemModelCreate_2a7190(s32 arg0)
{
    Obj *o;
    Params prm;
    Vec4 pos;

    MemStackAlign64_14d8e0(D_004DB3D0);
    o = MemStackNew_14e230(0x790, D_004DB3D0);
    if (o != NULL) {
        ModelObjExCtor_1c4920(o);
        *(u8 **)((u8 *)o + 0x1B0) = D_00470F50;
    }
    D_004824BC = o;
    if (o == NULL) {
        return;
    }
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x209);
    memset(&prm, 0, sizeof(prm));
    prm.unk30 = 8;
    prm.unk2C = prm.buf40;
    prm.unk3C = 8;
    prm.unk0 = arg0;
    prm.unk38 = prm.buf60;
    prm.unk4 = D_00461448;
    prm.unk8 = D_004DB3D0;
    prm.unkC = D_004DB3D0;
    prm.unk10 = D_004DB3D0;
    prm.unk14 = 0x209;
    prm.unk18 = 1;
    D_004824BC->v5C();
    D_004824BC->v50();
    InfoCfgParseAll_1afd00(D_004824BC, &prm);
    {
        f32 *pa = (f32 *)&pos;
        pa[0] = D_0047EC40;
        pa[1] = D_0047EC44;
        pa[2] = D_0047EC48;
        pa[3] = D_0047EC4C;
    }
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    ModelSetPos_151110(D_004824BC, &pos);
    {
        Obj *p = D_004824BC;
        Vec4 rot = {0};
        rot.x = 0.0f;
        rot.y = D_0047D5B0;
        rot.z = 0.0f;
        ModelSetRot_151080(p, &rot);
    }
    {
        Obj *p = D_004824BC;
        Vec4 sc = {0};
        sc.x = D_0047D278;
        sc.y = D_0047D278;
        sc.z = D_0047D278;
        ModelSetScale_150ff0(p, &sc);
    }
}
