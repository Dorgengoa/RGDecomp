#include "types.h"

/* $4 is an OUT-PARAMETER (same 16-byte {s16,s32,s32,s32} result as
   EffectArchiveLoadImgChecked_2e1930).  `idx` and `hv` are address-taken, which is why every entry
   address is recomputed from a fresh `lh` at each call site.  The two result
   members that are never assigned are read from uninitialised Res locals -
   retail loads both of them before the first branch. */

typedef struct Res {
    s16 a;                  /* 0x0 */
    s32 b;                  /* 0x4 */
    s32 c;                  /* 0x8 */
    s32 d;                  /* 0xC */
} Res;

typedef struct Sub {
    s16 h0;                 /* 0x0 */
    s16 h2;                 /* 0x2 */
    s32 f4;                 /* 0x4 */
    s16 h8;                 /* 0x8 */
    s16 hA;                 /* 0xA */
    s16 hC;                 /* 0xC */
    s16 hE;                 /* 0xE */
    s16 h10;                /* 0x10 */
    char name[0x20];        /* 0x12 */
    char text[0xA2];        /* 0x32 - sizes Ent to exactly 0xE0 */
} Sub;

typedef struct Ent {
    u8 pad0[0xC];
    Sub sub;                /* 0xC */
} Ent;

typedef struct Owner {
    Ent ents[48];           /* 0x0 */
    u32 f2A00;              /* 0x2A00 */
} Owner;

extern char D_00461798[];
extern char D_00461770[];
extern char D_00461778[];

extern s32 EffectFindByName_2dfe10(void *a, void *b, s16 *out);
extern void EffectFindFreeSlot_2dfdd0(void *a, s16 *out);
extern void StrReplaceExt_2dfd30(char *buf, void *a, char *fmt);
extern void Sprintf_1343b8(char *buf, char *a, void *b, char *c);
extern void EffectEntrySetHeaps_2dc540(Ent *e, void *a, u32 b, s32 idx);
extern void EffectEntrySetName_2d9550(Ent *e, void *a);
extern void *GetLoaderMgr_1f59d0(void);
extern s32 EffectEntryBuildChr_2dc0f0(Ent *e, s32 idx, void *a, void *b);
extern s32 EffectEntryLoadScript_2dbeb0(Ent *e, void *a, void *b);
extern s32 EffectEntryMeasureHeap_2dba80(Ent *e);
extern void EffectEntryReleaseByIdx_2de320(Owner *o, Res *r);
extern char *strcpy(char *dst, const char *src);

void EffectEntryLoadChr_2df7c0(Res *out, Owner *o, void *p2, void *p3, void *p4, void *p5,
                  void *p6, void *p7, void *p8, void *p9, s32 p10)
{
    s16 hv;                 /* 0x16E */
    s16 idx;                /* 0x16C */
    Res ra;                 /* 0x150 */
    Res rb;                 /* 0x140 */
    char buf1[0x40];        /* 0x100 */
    char buf2[0x40];        /* 0xC0  */
    Res t;                  /* 0xB0  */
    Sub *s;
    s32 got;
    s32 made;
    s32 id;

    hv = 0;
    if (EffectFindByName_2dfe10(o, p3, &hv) != 0) {
        got = hv;
        out->a = 2;
        out->b = got;
        out->c = 0;
        out->d = ra.d;
        return;
    }
    idx = -1;
    EffectFindFreeSlot_2dfdd0(o, &idx);
    if (idx < 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = rb.d;
        return;
    }
    StrReplaceExt_2dfd30(buf1, p4, D_00461798);
    Sprintf_1343b8(buf2, D_00461778, p5, D_00461770);
    s = &o->ents[idx].sub;
    EffectEntrySetHeaps_2dc540(&o->ents[idx], p2, o->f2A00, idx);
    EffectEntrySetName_2d9550(&o->ents[idx], p3);
    s->h8 = idx + 0x2DB;
    if (GetLoaderMgr_1f59d0() == 0) {
        out->a = 2;
        out->b = -1;
        out->c = 0;
        out->d = rb.d;
        return;
    }
    s->h0 = 0;
    s->h2 = idx;
    id = idx;
    s->f4 = p10;
    strcpy(s->name, buf1);
    strcpy(s->text, buf2);
    got = EffectEntryBuildChr_2dc0f0(&o->ents[idx], idx, p6, p7);
    made = EffectEntryLoadScript_2dbeb0(&o->ents[idx], p8, p9);
    if (got != 0 || made != 0) {
        t.c = 0;
        t.a = 2;
        t.b = s->h2;
        EffectEntryReleaseByIdx_2de320(o, &t);
    } else {
        EffectEntryMeasureHeap_2dba80(&o->ents[idx]);
        s->hE = -1;
        s->h10 = -1;
        s->hA = 1;
        s->hC = 1;
    }
    out->a = 2;
    out->b = id;
    out->c = 0;
    out->d = rb.d;
}
