#include "types.h"

typedef struct Item196670 {
    s8 *name;
    u8 pad4[0x2C];
} Item196670;

typedef struct Grp196670 {
    s8 *name;
    s32 count;
    Item196670 *items;
    s32 padC;
} Grp196670;

typedef struct Tbl196670 {
    s32 count;
    s32 pad4[3];
    Grp196670 groups[1];
} Tbl196670;

extern s32 Strcasecmp_1345b8(s8 *, s8 *);
extern s32 strcmp(s8 *, s8 *);

static inline Grp196670 *getGroup(Tbl196670 *t, s32 i)
{
    if (i < 0 || i >= t->count) {
        return 0;
    }
    return &t->groups[i];
}

static inline s32 findItem(Grp196670 *g, s8 *name)
{
    s32 j;

    if (name == 0 || *name == 0) {
        return -1;
    }
    for (j = 0; j < g->count; j++) {
        if (g->items[j].name == 0) {
            continue;
        }
        if (Strcasecmp_1345b8(g->items[j].name, name) == 0) {
            return j;
        }
    }
    return -1;
}

static inline Item196670 *getItem(Grp196670 *g, s32 j)
{
    if (j < 0 || j >= g->count) {
        return 0;
    }
    return &g->items[j];
}

Item196670 *SceneTableFindModelCfgEntry_196670(Tbl196670 *arg0, s8 *arg1, s8 *arg2)
{
    s32 i;
    Grp196670 *g;
    s32 idx;
    Item196670 *it;
    s8 *n;

    for (i = 0; ; i++) {
        g = getGroup(arg0, i);
        if (g == 0) {
            break;
        }
        n = g->name;
        if (arg2 != 0 && n != 0 && strcmp(arg2, n) != 0) {
            continue;
        }
        idx = findItem(g, arg1);
        if (idx < 0) {
            it = 0;
        } else {
            it = getItem(g, idx);
        }
        if (it != 0) {
            return it;
        }
    }
    return 0;
}
