#include "types.h"

typedef struct Rec2 {
    const char *name;
    u8 pad04[0x20];
} Rec2;

typedef struct Rec1 {
    s32   count;
    Rec2 *base;
    const char *name;
    u8    pad0C[0x8];
} Rec1;

typedef struct Tab1 {
    s32   count;
    Rec1 *base;
} Tab1;

typedef struct Ctx {
    u8 pad00[0x10];
} Ctx;

extern Ctx  *D_00481190;
extern Tab1 *D_00481188;
extern const char *SlotGetInt_15f720(void *p);
extern s32 strcmp(const char *a, const char *b);

static inline s32 find1(Tab1 *t, const char *key)
{
    s32 i;
    Rec1 *e;

    e = t->base;
    if (key == NULL) {
        return -1;
    }
    i = 0;
    while (i < t->count) {
        if (e->name != NULL) {
            if (strcmp(key, e->name) == 0) {
                return i;
            }
        }
        i++;
        e++;
    }
    return -1;
}

static inline Rec1 *at1(Tab1 *t, s32 i)
{
    if (i < 0 || i >= t->count) {
        return NULL;
    }
    return &t->base[i];
}

static inline s32 find2(Rec1 *t, const char *key)
{
    s32 j;
    Rec2 *e;

    if (key == NULL) {
        return -1;
    }
    e = t->base;
    j = 0;
    while (j < t->count) {
        if (e->name != NULL) {
            if (strcmp(key, e->name) == 0) {
                return j;
            }
        }
        j++;
        e++;
    }
    return -1;
}

static inline Rec2 *at2(Rec1 *t, s32 j)
{
    if (j < 0 || j >= t->count) {
        return NULL;
    }
    return &t->base[j];
}

s32 AmixerCfgTransFromCmd_16fc80(void *argv, s32 argc)
{
    Ctx *ctx;
    const char *k1;
    const char *k2;
    Tab1 *t1;
    Rec1 *p1;
    Rec2 *p2;

    if (D_00481190 == NULL) {
        return 0;
    }
    if (argc < 2) {
        return 0;
    }
    k1 = SlotGetInt_15f720(argv);
    k2 = SlotGetInt_15f720((u8 *)argv + 8);
    t1 = D_00481188;
    p1 = at1(t1, find1(t1, k1));
    if (p1 == NULL) {
        return 0;
    }
    p2 = at2(p1, find2(p1, k2));
    if (p2 == NULL) {
        return 0;
    }
    ctx = D_00481190;
    *(Rec2 **)((u8 *)ctx + 0x0) = p2;
    *(Rec1 **)((u8 *)ctx + 0x8) = p1;
    return 1;
}
