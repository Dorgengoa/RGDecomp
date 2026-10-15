#include "types.h"

typedef struct Ent { u8 pad0[0x190]; u32 x190; u8 pad194[0x1D0 - 0x194]; } Ent;
typedef struct Sub { u8 pad0[4]; s32 n; Ent *arr; } Sub;
typedef struct Mgr { u8 pad0[0x9C]; s32 n; Ent *arr; u8 padA4[4]; Sub subs[16]; } Mgr;

extern s32 VariantGetInt_15f780(void);
extern void *memset(void *, s32, s32);
extern Mgr *D_004812F4;
extern Ent *volatile D_00481304;
extern s32 D_00481308;

static inline Sub *getSub(Mgr *m, s32 i)
{
    if (!(i >= 0) || !(i < 16)) {
        return 0;
    }
    return &m->subs[i];
}

static inline Ent *subEnt(Sub *s, s32 i)
{
    if (i < 0 || i >= s->n || s->arr == 0) {
        return 0;
    } else {
        return &s->arr[i];
    }
}

static inline Ent *mgrEnt(Mgr *m, s32 i)
{
    if (i < 0 || i >= m->n) {
        return 0;
    } else {
        return &m->arr[i];
    }
}

s32 MapSceneCfgLightSet_193120(void)
{
    s32 i;
    Sub *s;
    Ent *e;

    i = VariantGetInt_15f780();
    s = getSub(D_004812F4, D_00481308);
    if (s != 0) {
        D_00481304 = subEnt(s, i);
    } else {
        D_00481304 = mgrEnt(D_004812F4, i);
    }
    e = D_00481304;
    if (e == 0) {
        return 0;
    }
    memset(e, 0, 0x1D0);
    D_00481304->x190 = 0xBF800000;
    return 1;
}
