/* rgp:protos */
#define RGP_SELF_CharaNpcResRequest_1f1600 1
#define RGP_SELF_initA 1
#define RGP_SELF_initB 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: ~18 locals across a 0x50-0x98 stack region interacting with
 * m2c's "(var_4*4)+sp" raw stack-pointer arithmetic and s64 arg1 sign
 * extension; 0 round trips spent. Needs asm/matchings/main/CharaNpcResRequest_1f1600.s
 * read by hand to pin the sp50..sp98 local layout before writing C -- too
 * many interacting fields to guess safely in one pass. Not attempted. */
/* s49m: MATCH */
#include "types.h"

typedef struct A {
    s32 a;
    s32 b;
    s32 c[7];
    s32 d;
} A;

typedef struct B {
    s32 w50;
    s32 w54;
    s32 w58;
    s32 w5C;
    s32 w60;
    s32 w64;
    char *w68;
    s32 w6C;
    s32 w70;
    s32 w74;
    s32 w78;
    s32 w7C;
    s32 w80;
    s32 w84;
} B;

typedef struct Src {
    s16 unk0;
    s16 pad2;
    s16 pad4;
    s16 unk6;
    char *unk8;
} Src;

typedef struct Res {
    u8 pad[0xC];
    Src *unkC;
} Res;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(char *, char *, char *);
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_0045B850[];

static inline void initA(A *p)
{
    s32 i;

    p->a = -1;
    p->b = -1;
    for (i = 0; i < 7; i++) {
        p->c[i] = -1;
    }
}

static inline void initB(B *p)
{
    p->w50 = -1;
    p->w54 = -1;
    p->w58 = -1;
    p->w5C = -1;
    p->w60 = -1;
    p->w64 = -1;
    p->w68 = NULL;
    p->w6C = -1;
    p->w70 = 0;
    p->w74 = -1;
    p->w78 = 0;
    p->w7C = 0;
    p->w80 = -1;
    p->w84 = 0;
}

s32 CharaNpcResRequest_1f1600(u8 *arg0, s16 arg1)
{
    char buf[0x100] __attribute__((aligned(16)));
    A a __attribute__((aligned(16)));
    B b __attribute__((aligned(16)));
    s32 m;
    u8 *e;
    Res *r;
    Src *s;
    s32 i;

    m = ((s32)GetCharaDataMgr_1fdb70());
    e = ((u8 *)GetWorldDataMgr_1fedf0());
    GetGameData_1fede0();
    r = ((Res *)GroupGetRecordById_41c2a0(*(s32 *)(e + 0x6C), (long long)(arg1), (long long)(-1), 1));
    if (r == NULL) {
        return 0;
    }
    s = r->unkC;
    if (s == NULL) {
        return 0;
    }
    initA(&a);
    a.a = s->unk0;
    a.b = 1;
    a.d = (s->unk6 << 10) / 16;
    a.c[0] = ((s->unk6 - 1) << 10) / 16;
    if (CharaDataFindById_1ed990(m, a.a) != 0) {
        return 1;
    }
    if (CharaDataCreate_1edab0(m, &a) == 0) {
        return 0;
    }
    initB(&b);
    b.w50 = s->unk0;
    b.w54 = 1;
    b.w60 = s->unk0;
    b.w58 = 0;
    b.w5C = 0;
    b.w6C = IdBitmapAlloc_1f5180(arg0 + 0xD04);
    b.w68 = buf;
    Sprintf_1343b8(buf, D_0045B850, s->unk8);
    CharaDataLoadSubRecById_1eda70(m, &b);
    LoaderQueueAppendSeparator_1cd670(((s32)GetLoaderMgr_1f59d0()));
    return 1;
}
