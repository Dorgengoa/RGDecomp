#include "types.h"

class Actor {
public:
    u8 pad0[0x1B0];
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
    virtual void f5C();
    u8 pad1B4[0x790 - 0x1B4];
};

typedef struct {
    s32 a0;
    s32 a4;
    s32 a8;
    s32 aC;
    s32 a10;
    s32 a14;
    s32 a18;
    u8 pad1C[0x2C - 0x1C];
    void *p2C;
    s32 n30;
    u8 pad34[0x38 - 0x34];
    void *p38;
    s32 n3C;
    u8 b40[0x20];
    u8 b60[0x28];
} Desc;

extern "C" {
extern void Sprintf_1343b8(char *, const char *, ...);
extern void MemStackAlign64_14d8e0(s32);
extern Actor *MemStackNew_14e230(s32, s32);
extern void NameTableFreeGroup_158ac0(u8 *, s32);
extern u8 *GetDrawCtxNameTable_15de40(void);
extern void InfoCfgParseAll_1afd00(Actor *, Desc *);
extern void ObjRecSetValue_1c3d60(s32, s32, s32, s32);
extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 RecStackGetSlot_1c4330(s32, s32);
extern void ModelObjExCtor_1c4920(Actor *);
extern void GameSceneObjBindMaybe_1cfcd0(s32, s32, Actor *, s32);
extern s32 ObjRecDefaultTexGroupMaybe_250440(s32);
extern s32 GetEffectMgr_2d9040(void);
extern void *memset(void *, s32, s32);
extern char *strcpy(char *, const char *);
extern char D_0045EB20[];
extern char D_0045EB70[];
extern char D_0045EB78[];
extern u8 D_00470F50[];
extern s32 D_0047E180;
}

extern "C" s32 EventCastCreateObj_24b8c0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, s32 p7)
{
    u8 *w;
    s32 id;
    s32 mdl;
    Actor *o;
    s32 k;
    s32 c;
    char name[0x20];
    char name2[0x20];
    Desc d;

    w = GetDrawCtxNameTable_15de40();
    id = RecStackGetSlot_1c4330(p1, p2);
    MemStackAlign64_14d8e0(id);
    mdl = ObjRecDefaultTexGroupMaybe_250440(p4);
    NameTableFreeGroup_158ac0(w, mdl);
    Sprintf_1343b8(name, D_0045EB70, p4);
    if (p4 >= 0x40 && p4 < 0x80) {
        strcpy((char *)(w + 0x1E4), name);
    }
    if (p6 == 0) {
        Sprintf_1343b8(name2, D_0045EB20);
    } else {
        Sprintf_1343b8(name2, D_0045EB78, p6);
    }
    o = MemStackNew_14e230(0x790, id);
    if (o != NULL) {
        ModelObjExCtor_1c4920(o);
        *(u8 **)((u8 *)o + 0x1B0) = D_00470F50;
    }
    o->f5C();
    k = GetEffectMgr_2d9040() + 0x58;
    *(s32 *)((u8 *)o + 0x53C) = k;
    if (k != 0) {
        c = D_0047E180;
        D_0047E180 = c + 1;
        *(s32 *)((u8 *)o + 0x538) = c;
    }
    memset(&d, 0, 0x88);
    d.n30 = 8;
    d.p2C = d.b40;
    d.p38 = d.b60;
    d.n3C = 8;
    d.a0 = p5;
    d.a4 = p6;
    d.a18 = p7;
    d.a8 = id;
    d.aC = id;
    d.a10 = id;
    d.a14 = mdl;
    InfoCfgParseAll_1afd00(o, &d);
    GameSceneObjBindMaybe_1cfcd0(p1, p4, o, 0);
    *(s32 *)((u8 *)o + 0x4DC) = mdl;
    if (p4 >= 0x40 && p4 < 0x80) {
        w[0x1E4] = 0;
    }
    ObjRecSetFlag2_1c3e80(p1, 1, p4);
    ObjRecSetValue_1c3d60(p1, 1, p4, 2);
    return 1;
}
