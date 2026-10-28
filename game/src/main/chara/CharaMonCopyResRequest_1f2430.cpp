/* rgp:protos */
#line 1
#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class VTbl {
public:
    VC_VPTR_MEMBER;                         
    u8 * get(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

class GObj {
public:
    VC_VPTR_MEMBER;                                                                                                                               
                                                                                                   
    u8 * Slot() { return VCM0(u8 *, 0x388); }
                 
    u8 * Main() { return VCM0(u8 *, 0x3C4); }
};

struct Rec {
    Rec() {
        a = -1;
        b = -1;
        c = -1;
        d = -1;
        e = -1;
        ptr = 0;
        f = -1;
        g = -1;
        h = 0;
        i = -1;
        l = -1;
        j = 0;
        k = 0;
        m = 0;
    }
    s32 a;          /* 0x00 */
    s32 b;          /* 0x04 */
    s32 c;          /* 0x08 */
    s32 d;          /* 0x0C */
    s32 e;          /* 0x10 */
    s32 f;          /* 0x14 */
    char *ptr;      /* 0x18 */
    s32 g;          /* 0x1C */
    s32 h;          /* 0x20 */
    s32 i;          /* 0x24 */
    s32 j;          /* 0x28 */
    s32 k;          /* 0x2C */
    s32 l;          /* 0x30 */
    s32 m;          /* 0x34 */
    u8 pad38[8];
};

typedef struct Req {
    s32 a;          /* 0x00 */
    s32 b;          /* 0x04 */
    s32 arr[7];     /* 0x08 */
    s32 len;        /* 0x24 */
    u8 pad28[8];
} Req;

typedef struct Def {
    s16 id;
    u8 pad2[6];
    s16 n;          /* 0x08 */
    u8 padA[6];
    char *s10;      /* 0x10 */
    char *s14;      /* 0x14 */
} Def;

typedef struct Ent {
    u8 pad0[0x8];
    Def *x8;        /* 0x08 */
    u8 flags;       /* 0x0A */
} Ent;

typedef struct Ent2 {
    u8 pad0[0xA];
    u8 flags;       /* 0x0A */
    u8 padB[0x15];
    Def *def;       /* 0x20 */
} Ent2;

typedef struct Sys {
    u8 pad0[0x40];
    struct { u8 pad0[0x8]; VTbl *tbl; } *m40;
    u8 pad44[0x60 - 0x44];
    struct { u8 pad0[0xC]; VTbl *tbl; } *m60;
    struct { u8 pad0[0xC]; VTbl *tbl; } *m64;
} Sys;

typedef struct Obj {
    u8 pad0[0xD04];
    u8 sub[0x10];   /* 0xD04 */
    s16 dD14;       /* 0xD14 */
} Obj;

typedef struct Gm {
    u8 pad0[0x14];
    s32 x14;
} Gm;

extern "C" {
s32 GetCharaDataMgr_1fdb70(void);
Sys *GetWorldDataMgr_1fedf0(void);
Gm *GetGameData_1fede0(void);
GObj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 CharaDataFindById_1ed990(s32, s32);
void CharaDataReleaseById_1ed850(s32, s32);
s32 CharaDataCreate_1edab0(s32, Req *);
s32 IdBitmapAlloc_1f5180(u8 *);
void Sprintf_1343b8(char *, char *, char *);
void CharaDataLoadSubRecById_1eda70(s32, Rec *);
char *CharaPcResNameBuildMaybe_40dc60(u8 *);
s32 GetLoaderMgr_1f59d0(void);
void LoaderQueueAppendSeparator_1cd670(s32);
s32 CharaResRequest_1f2d90(Obj *, s32, s32, long long, s32, s32, s32);
extern char D_0045B760[];
extern char D_0045B790[];
extern char D_0045B7F0[];
extern char D_0045B810[];
extern char D_0045B830[];
extern char D_0045B870[];
extern char D_0045B880[];
s32 CharaMonCopyResRequest_1f2430(Obj *o, s32 a1, s32 a2);
}

extern "C" s32 CharaMonCopyResRequest_1f2430(Obj *o, s32 a1, s32 a2)
{
    char buf[0x100] __attribute__((aligned(16)));
    Req q __attribute__((aligned(16)));
    s32 dm;
    Sys *sys;
    Gm *gm;
    GObj *obj;
    u8 *e;
    Def *d2;
    Ent2 *e2;
    Def *d;
    s32 i;
    s32 x;
    s32 v;
    u8 *p;

    dm = GetCharaDataMgr_1fdb70();
    sys = GetWorldDataMgr_1fedf0();
    gm = GetGameData_1fede0();
    {
        u8 *p_ = (u8 *)buf;
        u32 n_ = 0x100;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    obj = CharaMgrPoolFindByDataId_3a8a70(gm->x14, 0x2B00, 1, 1, 0, 0, 0);
    if (obj == 0) {
        return 0;
    }
    e = sys->m60->tbl->get(0x2B00);
    if (e == 0) {
        return 0;
    }
    d2 = *(Def **)(e + 8);
    e2 = (Ent2 *)sys->m64->tbl->get(0x2F11);
    if (e2 == 0) {
        return 0;
    }
    d = e2->def;
    q.a = -1;
    q.b = -1;
    for (i = 0; i < 7; i++) {
        q.arr[i] = -1;
    }
    q.a = 0x801;
    q.b = 1;
    q.arr[0] = (d->n << 10) / 16;
    q.arr[1] = (d2->n << 10) / 16;
    q.arr[2] = (*(s16 *)((u8 *)d2 + 0xE) << 10) / 16;
    q.arr[5] = 0x280;
    q.len = q.arr[0] + q.arr[1] + q.arr[2] + q.arr[4] + q.arr[5] + 0x1000;
    if (CharaDataFindById_1ed990(dm, q.a) != 0) {
        CharaDataReleaseById_1ed850(dm, q.a);
    }
    if (CharaDataCreate_1edab0(dm, &q) == 0) {
        return 0;
    }
    v = IdBitmapAlloc_1f5180(o->sub);
    {
        Rec r1 __attribute__((aligned(16)));
        r1.a = 0x801;
        r1.b = 1;
        r1.e = 0x801;
        r1.g = v;
        r1.c = 0;
        r1.d = 0;
        r1.ptr = buf;
        Sprintf_1343b8(buf, D_0045B7F0, D_0045B880);
        CharaDataLoadSubRecById_1eda70(dm, &r1);
    }
    p = obj->Main();
    if (p != 0) {
        p = *(u8 **)(p + 0x10);
    } else {
        p = sys->m40->tbl->get(*(s16 *)(e + 0x2A));
    }
    {
        Rec r2 __attribute__((aligned(16)));
        r2.g = v;
        r2.a = 0x801;
        r2.f = 0x801;
        r2.b = 1;
        r2.c = 1;
        r2.d = 1;
        r2.e = *(s16 *)p;
        r2.ptr = buf;
        Sprintf_1343b8(buf, D_0045B790, CharaPcResNameBuildMaybe_40dc60(p));
        CharaDataLoadSubRecById_1eda70(dm, &r2);
    }
    {
        Rec r3 __attribute__((aligned(16)));
        r3.a = 0x801;
        r3.b = 1;
        r3.d = 4;
        r3.e = 0;
        r3.c = 0;
        r3.ptr = buf;
        Sprintf_1343b8(buf, D_0045B810, d->s14);
        CharaDataLoadSubRecById_1eda70(dm, &r3);
    }
    if (e2->flags & 1) {
        Rec r4 __attribute__((aligned(16)));
        r4.a = 0x801;
        r4.e = 1;
        r4.d = 4;
        r4.b = 1;
        r4.c = 0;
        r4.ptr = buf;
        Sprintf_1343b8(buf, D_0045B830, d->s14);
        CharaDataLoadSubRecById_1eda70(dm, &r4);
    }
    if (o->dD14 != 0) {
        Rec r5 __attribute__((aligned(16)));
        r5.a = 0x801;
        r5.b = 1;
        r5.f = 0x801;
        r5.c = 5;
        r5.d = 5;
        r5.i = 5;
        r5.ptr = buf;
        Sprintf_1343b8(buf, D_0045B760, d->s10);
        CharaDataLoadSubRecById_1eda70(dm, &r5);
    }
    p = obj->Slot();
    if (p != 0) {
        p = *(u8 **)(p + 0x10);
    } else {
        p = sys->m40->tbl->get(*(s16 *)(e + 0x26));
    }
    {
        Rec r6 __attribute__((aligned(16)));
        r6.a = 0x801;
        r6.e = *(s16 *)p;
        r6.b = 1;
        r6.c = 2;
        r6.d = 0;
        r6.g = IdBitmapAlloc_1f5180(o->sub);
        r6.ptr = buf;
        Sprintf_1343b8(buf, D_0045B870, CharaPcResNameBuildMaybe_40dc60(p));
        CharaDataLoadSubRecById_1eda70(dm, &r6);
    }
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    return CharaResRequest_1f2d90(o, a1, a2, (long long)(0x2F11), 0x801, 1, 2);
}
