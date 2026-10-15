#include "types.h"

typedef unsigned __int128 u128;

struct Vec4 {
    f32 x, y, z, w;
};

struct Pad1B0 {
    u8 pad0[0x180];
    u128 x180;
    u8 pad190[0x20];
};

class Model : public Pad1B0 {
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
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void v50();
    virtual void d19();
    virtual void d20();
    virtual void v5C();
};

struct PadC0 {
    u8 pad0[0xC0];
};

class Cam : public PadC0 {
public:
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void c6();
    virtual void c7();
    virtual void c8();
    virtual void c9();
    virtual void c10();
    virtual void c11();
    virtual void c12();
    virtual void c13();
    virtual void c14();
    virtual void c15();
    virtual void c16();
    virtual void c17();
    virtual void c18();
    virtual void c19();
    virtual void c20();
    virtual void c21();
    virtual void c22();
    virtual void c23();
    virtual void c24();
    virtual void c25();
    virtual void c26();
    virtual void c27();
    virtual void c28();
    virtual void c29();
    virtual void c30();
    virtual void c31();
    virtual void c32();
    virtual void c33();
    virtual void c34();
    virtual void c35();
    virtual void c36();
    virtual void c37();
    virtual void c38();
    virtual void c39();
    virtual void c40();
    virtual void c41();
    virtual void c42();
    virtual void c43();
    virtual void c44();
    virtual void c45();
    virtual void c46();
    virtual void c47();
    virtual void v8(f32);
};

struct Desc {
    void *x00;
    void *x04;
    void *x08;
    void *x0C;
    void *x10;
    s32 x14;
    s32 x18;
    u8 pad1C[0x2C - 0x1C];
    void *x2C;
    s32 x30;
    u8 pad34[4];
    void *x38;
    s32 x3C;
    u8 buf40[0x20];
    u8 buf60[0x38];
};

struct Ent {
    u8 pad0[0x5C];
    u8 x5C[0x238 - 0x5C];
    s32 x238;
    s32 x23C;
    s32 x240;
    u8 pad244[0xC];
    Model *x250;
    s32 x254;
    s32 x258;
    f32 x25C;
    u8 x260[0x10];
    u8 x270;
};

struct Info {
    u8 pad0[0x14];
    f32 x14;
    f32 x18;
};

extern "C" {
void *GetLoaderMgr_1f59d0(void);
s32 LoaderGetStatus_1cd4f0(void *, s32);
void *LoaderGetData_1cd490(void *, s32, s32 *);
void LoaderReleaseById_1cd340(void *, s32);
void MemStackAlign64_14d8e0(void *);
void *MemStackNew_14e230(s32, void *);
void ModelObjExCtor_1c4920(void *);
u8 *GetDrawCtxNameTable_15de40(void);
void NameTableFreeGroup_158ac0(u8 *, s32);
void *memset(void *, s32, u32);
void Sprintf_1343b8(char *, const char *);
char *strcpy(char *, const char *);
void InfoCfgParseAll_1afd00(Model *, Desc *);
void ModelSetPos_151110(Model *, Vec4 *);
void ModelSetRot_151080(Model *, Vec4 *);
void ModelSetScale_150ff0(Model *, Vec4 *);
void ModelObjPlayMotionByName_1867a0(Model *, const char *, s32);
u8 ModelHasMotion_20a5b0(Model *, const char *);
u8 *GetGameData_1fede0(void);
Info *DataTableFindRowById_3fd770(void *, s16);
void CameraSetLag_177170(Cam *, f32, f32);
void VecNormalize_13bd90(void *, Vec4 *);
}

extern char D_00462C68[];
extern char D_00462C78[];
extern char D_00462C80[];
extern char D_00462C90[];
extern char D_00462C98[];
extern char D_00462CA0[];
extern u8 D_00470F50[];
extern s32 D_0047E180;
extern Vec4 D_0047F820 __attribute__((section(".sdata")));
extern Vec4 D_0047F880 __attribute__((section(".sdata")));
extern Vec4 D_0047F890 __attribute__((section(".sdata")));
extern void *D_00482338;
extern Cam *D_004823D4;

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

#pragma opt_dead_assignments off
extern "C" s32 MenuMobPreviewLoadPoll_35eee0(Ent *a) {
    void *mgr;
    s32 r;
    void *data;
    Model *o;
    u8 *t;
    s32 c1;
    s32 c2;
    s32 id;
    Info *p;
    f32 sc;
    s32 *lk;
    s32 out;
    s32 n;
    f32 f1;
    volatile Vec4 *vv;
    Desc desc;
    char buf[0x10];
    Vec4 pos;
    Vec4 A;
    Vec4 B;
    Vec4 v;
    Vec4 s;
    Vec4 k;
    Vec4 k2;

    if (a->x23C != 0) return 0;
    if (a->x238 == -1) return 0;
    mgr = GetLoaderMgr_1f59d0();
    a->x23C = r = LoaderGetStatus_1cd4f0(mgr, a->x238);
    if (r == 1) {
        a->x270 = 1;
        data = LoaderGetData_1cd490(mgr, a->x238, &out);
        MemStackAlign64_14d8e0(D_00482338);
        o = (Model *)MemStackNew_14e230(0x790, D_00482338);
        if (o != 0) {
            ModelObjExCtor_1c4920(o);
            *(void **)((u8 *)o + 0x1B0) = D_00470F50;
        }
        a->x250 = o;
        if (o == 0) return 0;
        t = GetDrawCtxNameTable_15de40();
        NameTableFreeGroup_158ac0(t, 0x209);
        memset(&desc, 0, 0x88);
        desc.x30 = 8;
        desc.x08 = D_00482338;
        desc.x00 = data;
        desc.x0C = D_00482338;
        desc.x2C = desc.buf40;
        desc.x3C = 8;
        desc.x10 = D_00482338;
        desc.x38 = desc.buf60;
        desc.x04 = D_00462C68;
        desc.x14 = 0x209;
        desc.x18 = 1;
        Sprintf_1343b8(buf, D_00462C78);
        strcpy((char *)t + 0x1E4, buf);
        a->x250->v5C();
        a->x250->v50();
        o = a->x250;
        lk = (s32 *)a->x5C;
        *(s32 **)((u8 *)o + 0x53C) = lk;
        if (lk != 0) {
            n = D_0047E180;
            D_0047E180 = n + 1;
            *(s32 *)((u8 *)o + 0x538) = n;
        }
        InfoCfgParseAll_1afd00(a->x250, &desc);
        o = a->x250;
        vv = (volatile Vec4 *)&v;
        vv->x = D_0047F820.x;
        vv->y = D_0047F820.y;
        vv->z = D_0047F820.z;
        vv->w = D_0047F820.w;
        vv->x = 8.0f;
        vv->y = -18.0f;
        vv->z = 0.0f;
        ModelSetPos_151110(o, &v);
        o = a->x250;
        ZERO16(&s);
        s.x = 0.0f;
        s.y = 0.0f;
        s.z = 0.0f;
        ModelSetRot_151080(o, &s);
        o = a->x250;
        ZERO16(&k);
        k.x = 1.0f;
        k.y = 1.0f;
        k.z = 1.0f;
        ModelSetScale_150ff0(o, &k);
        t[0x1E4] = 0;
        if (a->x240 == 0x2EE1) {
            ModelObjPlayMotionByName_1867a0(a->x250, D_00462C80, 0);
        } else {
            c1 = ModelHasMotion_20a5b0(a->x250, D_00462C90);
            c2 = ModelHasMotion_20a5b0(a->x250, D_00462C98);
            if (c1 != 0 && c2 != 0) {
                ModelObjPlayMotionByName_1867a0(a->x250, D_00462C90, 0);
            } else {
                ModelObjPlayMotionByName_1867a0(a->x250, D_00462CA0, 0);
            }
        }
        id = a->x240;
        p = DataTableFindRowById_3fd770(*(void **)(*(u8 **)(*(u8 **)(GetGameData_1fede0() + 8) + 0x94) + 0xC), id);
        if (p != 0) {
            *(u128 *)&pos = a->x250->x180;
            sc = p->x18;
            pos.y = -18.0f + p->x14;
            ModelSetPos_151110(a->x250, &pos);
            o = a->x250;
            ZERO16(&k2);
            k2.x = sc;
            k2.y = sc;
            k2.z = sc;
            ModelSetScale_150ff0(o, &k2);
            a->x254 = 0;
        }
        LoaderReleaseById_1cd340(mgr, a->x238);
        a->x238 = -1;
        a->x258 = 0;
        if (D_004823D4 != 0) {
            { f32 *pa = (f32 *)&A; pa[0] = D_0047F880.x; pa[1] = D_0047F880.y; pa[2] = D_0047F880.z; pa[3] = D_0047F880.w; }
            { f32 *pb = (f32 *)&B; pb[0] = D_0047F890.x; pb[1] = D_0047F890.y; pb[2] = D_0047F890.z; pb[3] = D_0047F890.w; }
            a->x25C = 150.0f;
            if (a->x240 == 0x2EE1) {
                B.y = 36.0f;
                B.z = 572.0f;
                A.y = 36.0f;
                a->x25C = 572.0f;
            }
            f1 = 1.0f;
            *(u128 *)((u8 *)D_004823D4 + 0xE0) = *(u128 *)&A;
            *(u128 *)((u8 *)D_004823D4 + 0xF0) = *(u128 *)&B;
            CameraSetLag_177170(D_004823D4, f1, -1.0f);
            D_004823D4->v8(-1.0f);
            VecNormalize_13bd90(a->x260, &B);
        }
    }
    return 1;
}
