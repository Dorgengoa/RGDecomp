#include "types.h"
#pragma optimization_level 3

typedef struct Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct Desc {
    void *h;        /* 0x00 */
    void *name;     /* 0x04 */
    void *a, *b, *c;/* 0x08 */
    s32 id;         /* 0x14 */
    s32 one;        /* 0x18 */
    s32 pad1C[4];   /* 0x1C */
    void *p0;       /* 0x2C */
    s32 n0;         /* 0x30 */
    s32 pad34;      /* 0x34 */
    void *p1;       /* 0x38 */
    s32 n1;         /* 0x3C */
    u8 buf0[0x20];  /* 0x40 */
    u8 buf1[0x30];  /* 0x60 */
} Desc;

struct VB { u8 d[0x1B0]; };
struct VO : VB {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
    virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13(); virtual void f14();
    virtual void f15(f32);
    virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
    virtual void f20();
    virtual void f21();
};

typedef struct Ent {
    s32 id;
    s32 st;
} Ent;

typedef struct R3 { u8 pad[0xC]; s32 fC; } R3;
typedef struct R2 { u8 pad[0x18]; R3 *f18; } R2;
typedef struct Q { u8 pad[4]; R2 *f4; } Q;
typedef struct R { u8 pad[4]; s16 f4; } R;

extern "C" {
void MemStackAlign64_14d8e0(void *);
void MemStackPeekQw_14d9d0(void *, s32);
void ModelSetScale_150ff0(VO *, Vec4 *);
void ModelSetRot_151080(VO *, Vec4 *);
void ModelSetPos_151110(VO *, Vec4 *);
void *GetDrawCtxNameTable_15de40(void);
void ModelObjPlayMotionByName_1867a0(VO *, void *, s32);
void InfoCfgParseAll_1afd00(VO *, Desc *);
void LoaderReleaseById_1cd340(void *, s32);
void *LoaderGetData_1cd490(void *, s32, s32 *);
s32 LoaderGetStatus_1cd4f0(void *, s32);
void *GetLoaderMgr_1f59d0(void);
s32 MsgTableLoadFromArchive_202a50(void *, void *, void *);
void TexGroupLoadFromArchive_202be0(void *, void *, void *, s32, s32);
Q *GetSelectedInsectEntryMaybe_206ad0(void);
void InsectModelApplyColorRec_3913f0(VO *, s32, s32);
void InsectCageAdjTableParse_391720(void *, void *, s32, s32);
void ModelSetDesignVisible_391860(VO *, R *, s32);
void InsectMenuScreenInit_398210(void *);
R *CageRecGetCatchDef_3d09c0(R2 *);
void *memset(void *, s32, u32);
extern Ent D_00454410[];
extern u8 D_00464310[];
extern u8 D_00464318[];
extern u8 D_00464330[];
extern u8 D_00464350[];
extern f32 D_0047D410;
extern f32 D_0047D930;
extern f32 D_0047FF30;
extern f32 D_0047FF34;
extern f32 D_0047FF38;
extern f32 D_0047FF3C;
extern s16 D_0047FF4C;
extern s16 D_0047FF54;
extern void *D_004834E8;
extern s32 D_004834FC;
extern s16 D_00483508;
extern VO *D_00483518;
extern s8 D_0048352C;
extern u8 D_00483550[4];
extern s32 D_00483560;
}

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) { while (n_) { *p_ = 0; n_--; p_++; } } }

extern "C" s32 InsectMenuResLoadPoll_398420(void) {
    s32 sz;
    Desc d;
    volatile Vec4 v;
    void *ctx;
    s32 sum;
    s32 n;
    s32 i;
    Ent *e;
    s32 *st;
    void *p;
    Q *q;
    R *r;

    ctx = GetLoaderMgr_1f59d0();
    sum = 0;
    n = 1;
    if (D_0047FF4C != 0) {
        if (D_0047FF54 < 0) {
            goto loop;
        }
        n += 2;
    }
loop:
    for (i = 0; i < n; i++) {
        e = &D_00454410[i];
        st = &e->st;
        if (*st != 0) {
            continue;
        }
        if (e->id == -1) {
            continue;
        }
        if ((*st = LoaderGetStatus_1cd4f0(ctx, e->id)) != 1) {
            continue;
        }
        GetDrawCtxNameTable_15de40();
        MemStackAlign64_14d8e0(D_004834E8);
        MemStackPeekQw_14d9d0(D_004834E8, 1);
        p = LoaderGetData_1cd490(ctx, e->id, &sz);
        if (i == 2) {
            InsectCageAdjTableParse_391720(D_004834E8, p, sz, 0);
            ModelObjPlayMotionByName_1867a0(D_00483518, D_00483550, 4);
            D_00483518->f15(1.0f);
            ModelObjPlayMotionByName_1867a0(D_00483518, D_00464310, 4);
            D_00483518->f15(1.0f);
            q = GetSelectedInsectEntryMaybe_206ad0();
            r = CageRecGetCatchDef_3d09c0(q->f4);
            ModelSetDesignVisible_391860(D_00483518, r, D_0047FF54);
            InsectModelApplyColorRec_3913f0(D_00483518, r->f4, q->f4->f18->fC);
            D_00483560 = r->f4;
            D_0048352C = 1;
        } else if (i == 1) {
            memset(&d, 0, 0x88);
            d.h = p;
            d.a = D_004834E8;
            d.n0 = 8;
            d.b = D_004834E8;
            d.p0 = d.buf0;
            d.n1 = 8;
            d.p1 = d.buf1;
            d.name = D_00464318;
            d.c = D_004834E8;
            d.id = 0x32E;
            d.one = 1;
            D_00483518->f21();
            InfoCfgParseAll_1afd00(D_00483518, &d);
            v.x = D_0047FF30;
            v.y = D_0047FF34;
            v.z = D_0047FF38;
            v.w = D_0047FF3C;
            v.z = 65.0f;
            v.x = 0.0f;
            v.y = 0.0f;
            ModelSetPos_151110(D_00483518, (Vec4 *)&v);
            {
                VO *o = D_00483518;
                Vec4 a;
                BZERO(&a, 16);
                a.x = D_0047D410;
                a.y = D_0047D930;
                a.z = 0.0f;
                ModelSetRot_151080(o, &a);
            }
            {
                VO *o = D_00483518;
                Vec4 b;
                BZERO(&b, 16);
                b.x = 1.0f;
                b.y = 1.0f;
                b.z = 1.0f;
                ModelSetScale_150ff0(o, &b);
            }
            *(s32 *)((u8 *)D_00483518 + 0x450) = 0;
        } else if (i == 0) {
            InsectMenuScreenInit_398210(p);
            D_004834FC = MsgTableLoadFromArchive_202a50(p, D_00464330, D_004834E8);
            TexGroupLoadFromArchive_202be0(p, D_00464350, D_004834E8, 0x32D, 0);
        }
        LoaderReleaseById_1cd340(ctx, D_00454410[i].id);
        D_00454410[i].id = -1;
    }
    for (i = 0; i < n; i++) {
        sum += D_00454410[i].st;
    }
    if (sum == n) {
        D_00483508 = 1;
        return 1;
    }
    return 0;
}
