/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

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
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v50() { VCM0(void, 0x50); }
    
    
    void v5C() { VCM0(void, 0x5C); }
};

struct PadC0 {
    u8 pad0[0xC0];
};

class Cam : public PadC0 {
public:
    VC_VPTR_MEMBER;
    void c1() { VCM0(void, 0xC); }
    void c2() { VCM0(void, 0x10); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v8(f32 a0) { VCM(void, (void *, f32), 0xC8, a0); }
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
void ModelObjExCtor_1c4920(void *, int, int, int);
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

extern "C" char D_00462C68[];
extern "C" char D_00462C78[];
extern "C" char D_00462C80[];
extern "C" char D_00462C90[];
extern "C" char D_00462C98[];
extern "C" char D_00462CA0[];
extern "C" u8 D_00470F50[];
extern "C" s32 D_0047E180;
extern "C" Vec4 D_0047F820 __attribute__((section(".sdata")));
extern "C" Vec4 D_0047F880 __attribute__((section(".sdata")));
extern "C" Vec4 D_0047F890 __attribute__((section(".sdata")));
extern "C" void *D_00482338;
extern "C" Cam *D_004823D4;

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
    Desc desc __attribute__((aligned(16)));
    char buf[0x10] __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 A __attribute__((aligned(16)));
    Vec4 B __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    Vec4 s __attribute__((aligned(16)));
    Vec4 k __attribute__((aligned(16)));
    Vec4 k2 __attribute__((aligned(16)));

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
            ModelObjExCtor_1c4920(o, 0, 0, 0);
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
