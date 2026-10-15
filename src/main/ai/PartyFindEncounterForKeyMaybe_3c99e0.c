#include "types.h"

typedef struct Slot { u8 pad[0x38]; } Slot;
typedef struct Ctx8 { s32 a; s32 b; Slot slots[64]; u8 tail[0x14]; } Ctx8;

typedef struct Rule {
    u8 pad0[0x20];
    s16 m20;
    s16 m22;
    s32 m24;
    s32 m28;
} Rule;

typedef struct Link {
    s16 id;
    s16 pad2;
    Rule *rule;
} Link;

typedef struct Actor {
    u8 pad0[0x3A];
    s16 m3A;
    s16 m3C;
    struct { s16 key; s16 id; } t2[8];
    struct { s16 key; s16 id; } t1[8];
} Actor;

typedef struct Sys {
    u8 pad0[0x70];
    s32 m70;
} Sys;

extern s32 VariantIsZero_36ed10(s32);
extern void VariantInit_36ff00(Slot *);
extern s32 ScriptExecOpStream_3dffa0(Ctx8 *, s32, s32, s32);
extern void VariantPoolReset_3e01f0(Ctx8 *);
extern s32 GroupFindByKey_4022b0(s32, s32);
extern Link *DataTableSortedIndexFindRange_403570(s32, s16, s32 *);
extern Sys *D_00483894;

static __inline s32 check(Ctx8 *c, s32 a, s32 b)
{
    s32 r;
    if (a <= 0) {
        return 1;
    }
    if (b == 0) {
        return 1;
    }
    r = ScriptExecOpStream_3dffa0(c, a, b, 0);
    if (r == 0) {
        return 0;
    }
    if (VariantIsZero_36ed10(r) != 0) {
        return 0;
    }
    return 1;
}

Rule *PartyFindEncounterForKeyMaybe_3c99e0(Actor *arg0, s32 arg1, s32 *arg2)
{
    Ctx8 ctx;
    s32 cnt;
    Slot *p;
    s32 h;
    s32 type;
    s32 n;
    s32 j;
    s32 key;
    s32 id;
    Link *l;
    Rule *r;
    s32 t;

    if (D_00483894 == NULL) {
        return NULL;
    }
    h = 0;
    if (D_00483894->m70 != 0) {
        h = GroupFindByKey_4022b0(D_00483894->m70, arg1);
    }
    if (h == 0) {
        return NULL;
    }
    p = ctx.slots;
    do {
        VariantInit_36ff00(p);
        p++;
    } while (p < &ctx.slots[64]);
    VariantPoolReset_3e01f0(&ctx);
    for (type = 1; type <= 2; type++) {
        n = 0;
        switch (type) {
        case 1:
            n = arg0->m3C;
            break;
        case 2:
            n = arg0->m3A;
            break;
        }
        if (n <= 0) {
            continue;
        }
        for (j = 0; j < n; j++) {
            key = -1;
            id = key;
            switch (type) {
            case 1:
                key = arg0->t1[j].key;
                id = arg0->t1[j].id;
                break;
            case 2:
                key = arg0->t2[j].key;
                id = arg0->t2[j].id;
                break;
            }
            if (arg1 != key) {
                continue;
            }
            cnt = 0;
            l = DataTableSortedIndexFindRange_403570(h, id, &cnt);
            if (l == NULL) {
                continue;
            }
            while (l->id == id && cnt > 0) {
                r = l->rule;
                if (r != NULL
                    && (r->m20 <= 0 || r->m24 == 0 || ((t = ScriptExecOpStream_3dffa0(&ctx, r->m20, r->m24, 0)) != 0 && VariantIsZero_36ed10(t) == 0))
                    && (r->m22 <= 0 || r->m28 == 0 || ((t = ScriptExecOpStream_3dffa0(&ctx, r->m22, r->m28, 0)) != 0 && VariantIsZero_36ed10(t) == 0))) {
                    *arg2 = id;
                    return r;
                }
                l++;
                cnt--;
            }
        }
    }
    return NULL;
}
