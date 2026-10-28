/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v50() { VCM0(void, 0x50); }
    
    
    void v5C() { VCM0(void, 0x5C); }
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
void ModelObjExCtor_1c4920(Obj *, int, int, int);
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
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Params)) + (0x88) + (0x90)];
    Vec4 pos __attribute__((aligned(16)));

    MemStackAlign64_14d8e0(D_004DB3D0);
    o = MemStackNew_14e230(0x790, D_004DB3D0);
    if (o != NULL) {
        ModelObjExCtor_1c4920(o, 0, 0, 0);
        *(u8 **)((u8 *)o + 0x1B0) = D_00470F50;
    }
    D_004824BC = o;
    if (o == NULL) {
        return;
    }
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x209);
    memset(&(*(Params *)(rgp_blk1 + 0x0)), 0, sizeof((*(Params *)(rgp_blk1 + 0x0))));
    (*(Params *)(rgp_blk1 + 0x0)).unk30 = 8;
    (*(Params *)(rgp_blk1 + 0x0)).unk2C = (*(Params *)(rgp_blk1 + 0x0)).buf40;
    (*(Params *)(rgp_blk1 + 0x0)).unk3C = 8;
    (*(Params *)(rgp_blk1 + 0x0)).unk0 = arg0;
    (*(Params *)(rgp_blk1 + 0x0)).unk38 = (*(Params *)(rgp_blk1 + 0x0)).buf60;
    (*(Params *)(rgp_blk1 + 0x0)).unk4 = D_00461448;
    (*(Params *)(rgp_blk1 + 0x0)).unk8 = D_004DB3D0;
    (*(Params *)(rgp_blk1 + 0x0)).unkC = D_004DB3D0;
    (*(Params *)(rgp_blk1 + 0x0)).unk10 = D_004DB3D0;
    (*(Params *)(rgp_blk1 + 0x0)).unk14 = 0x209;
    (*(Params *)(rgp_blk1 + 0x0)).unk18 = 1;
    D_004824BC->v5C();
    D_004824BC->v50();
    InfoCfgParseAll_1afd00(D_004824BC, &(*(Params *)(rgp_blk1 + 0x0)));
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
        Vec4 rot __attribute__((aligned(16))) = {0};
        rot.x = 0.0f;
        rot.y = D_0047D5B0;
        rot.z = 0.0f;
        ModelSetRot_151080(p, &rot);
    }
    {
        Obj *p = D_004824BC;
        Vec4 sc __attribute__((aligned(16))) = {0};
        sc.x = D_0047D278;
        sc.y = D_0047D278;
        sc.z = D_0047D278;
        ModelSetScale_150ff0(p, &sc);
    }
}
