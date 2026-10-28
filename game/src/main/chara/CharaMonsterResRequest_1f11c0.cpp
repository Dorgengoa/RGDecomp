#include "types.h"

class VTbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * get(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

struct Rec {
    Rec() {
        ptr = 0;
        a = -1;
        b = -1;
        c = -1;
        d = -1;
        e = -1;
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
    s16 id;         /* 0x00 */
    u8 pad2[3];
    s8 nib : 4;     /* 0x05 */
    s8 hi : 4;
    u8 pad6[2];
    s16 n;          /* 0x08 */
    u8 padA[2];
    char *name;     /* 0x0C */
    char *s10;      /* 0x10 */
    char *s14;      /* 0x14 */
} Def;

typedef struct Ent {
    u8 pad0[0xA];
    u8 flags;       /* 0x0A */
    u8 padB[0x15];
    Def *def;       /* 0x20 */
} Ent;

typedef struct Sys {
    u8 pad0[0x64];
    struct { u8 pad0[0xC]; VTbl *tbl; } *m64;
} Sys;

typedef struct Obj {
    u8 pad0[0xD04];
    u8 sub[0x10];   /* 0xD04 */
    s16 dD14;       /* 0xD14 */
} Obj;

extern "C" {
s32 GetCharaDataMgr_1fdb70(void);
Sys *GetWorldDataMgr_1fedf0(void);
void GetGameData_1fede0(void);
s32 CharaDataFindById_1ed990(s32, s32);
s32 CharaDataCreate_1edab0(s32, Req *);
s32 IdBitmapAlloc_1f5180(u8 *);
void Sprintf_1343b8(char *, char *, char *);
void CharaDataLoadSubRecById_1eda70(s32, Rec *);
s32 MonDefBuildBt1Path_41b530(char **, char *, s32);
s32 GetLoaderMgr_1f59d0(void);
void LoaderQueueAppendSeparator_1cd670(s32);
extern char D_0045B760[];
extern char D_0045B7F0[];
extern char D_0045B810[];
extern char D_0045B830[];
}

extern "C" s32 CharaMonsterResRequest_1f11c0(Obj *o, s32 id)
{
    char buf2[0x100] __attribute__((aligned(16)));
    char buf1[0x100] __attribute__((aligned(16)));
    Req q __attribute__((aligned(16)));
    s32 dm;
    Sys *sys;
    Ent *e;
    Def *d;
    s32 i;
    s32 x;
    s32 v;

    dm = GetCharaDataMgr_1fdb70();
    sys = GetWorldDataMgr_1fedf0();
    GetGameData_1fede0();
    e = (Ent *)sys->m64->tbl->get((s16)id);
    if (e == 0) {
        return 0;
    }
    d = e->def;
    if (d == 0) {
        return 0;
    }
    q.a = -1;
    q.b = -1;
    for (i = 0; i < 7; i++) {
        q.arr[i] = -1;
    }
    q.a = d->id;
    q.b = 1;
    q.len = (d->n << 10) / 16;
    q.arr[5] = 0x200;
    x = ((d->n - 1) << 10) / 16;
    q.arr[0] = x - q.arr[5];
    if (CharaDataFindById_1ed990(dm, q.a) != 0) {
        return 1;
    }
    if (CharaDataCreate_1edab0(dm, &q) == 0) {
        return 0;
    }
    v = IdBitmapAlloc_1f5180(o->sub);
    Rec r1 __attribute__((aligned(16)));
    r1.a = d->id;
    r1.b = 1;
    r1.e = d->id;
    r1.c = 0;
    r1.d = 0;
    r1.g = v;
    r1.ptr = buf2;
    r1.j = d->nib;
    Sprintf_1343b8(buf2, D_0045B7F0, d->name);
    CharaDataLoadSubRecById_1eda70(dm, &r1);
    if (MonDefBuildBt1Path_41b530(&d->name, buf1, 0) != 0) {
        Rec r2 __attribute__((aligned(16)));
        r2.a = d->id;
        r2.b = 1;
        r2.d = 2;
        r2.e = d->id;
        r2.f = d->id;
        r2.ptr = buf2;
        r2.g = v;
        r2.c = 0;
        Sprintf_1343b8(buf2, D_0045B7F0, buf1);
        CharaDataLoadSubRecById_1eda70(dm, &r2);
    }
    Rec r3 __attribute__((aligned(16)));
    r3.a = d->id;
    r3.b = 1;
    r3.d = 4;
    r3.e = 0;
    r3.c = 0;
    r3.ptr = buf2;
    Sprintf_1343b8(buf2, D_0045B810, d->s14);
    CharaDataLoadSubRecById_1eda70(dm, &r3);
    if (e->flags & 1) {
        Rec r4 __attribute__((aligned(16)));
        r4.a = d->id;
        r4.e = 1;
        r4.d = 4;
        r4.b = 1;
        r4.c = 0;
        r4.ptr = buf2;
        Sprintf_1343b8(buf2, D_0045B830, d->s14);
        CharaDataLoadSubRecById_1eda70(dm, &r4);
    }
    if (o->dD14 != 0) {
        Rec r5 __attribute__((aligned(16)));
        r5.a = d->id;
        r5.b = 1;
        r5.f = d->id;
        r5.c = 5;
        r5.d = 5;
        r5.i = 5;
        r5.ptr = buf2;
        Sprintf_1343b8(buf2, D_0045B760, d->s10);
        CharaDataLoadSubRecById_1eda70(dm, &r5);
    }
    LoaderQueueAppendSeparator_1cd670(GetLoaderMgr_1f59d0());
    return 1;
}
