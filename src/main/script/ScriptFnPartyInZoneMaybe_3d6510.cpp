#pragma optimization_level 3
#include "types.h"

struct Ent4 {
    s16 v;
    s16 pad;
};

struct Sub {
    u8 pad0[0x3A];
    s16 n3A;
    s16 n3C;
    u8 pad3E[2];
    Ent4 a40[8];
    Ent4 a60[8];
};

struct Mgr {
    u8 pad0[0x18];
    Sub *sub;
};

extern "C" {
extern void VariantSetS32_36f040(s32, s32, s32, Mgr *, s32);
extern s16 VariantGetS16_36fcc0(s32);
extern Mgr *D_00483960;
extern s32 D_00483964;
}

static inline s32 get40(Mgr *m, s32 i) {
    Sub *s = m->sub;
    if (i >= 0 && i < 8) {
        return s->a40[i].v;
    }
    return -1;
}

static inline s32 get60(Mgr *m, s32 i) {
    Sub *s = m->sub;
    if (i >= 0 && i < 8) {
        return s->a60[i].v;
    }
    return -1;
}

extern "C" void ScriptFnPartyInZoneMaybe_3d6510(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    bool found;
    s32 type;
    s32 x;
    s32 ux;
    s32 n;
    s32 v;
    Mgr *um;
    s32 i;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1, um, ux);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if ((arg3 == 0) || (arg2 <= 0)) return;
    x = VariantGetS16_36fcc0(arg3);
    found = false;
    for (type = 1; type <= 2; type++) {
        n = 0;
        switch (type) {
        case 1:
            n = D_00483960->sub->n3C;
            break;
        case 2:
            n = D_00483960->sub->n3A;
            break;
        }
        for (i = 0; i < n; i++) {
            v = -1;
            switch (type) {
            case 1:
                v = get60(D_00483960, i);
                break;
            case 2:
                v = get40(D_00483960, i);
                break;
            }
            if (x == v) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    VariantSetS32_36f040(arg0, found, 1, D_00483960, x);
}
