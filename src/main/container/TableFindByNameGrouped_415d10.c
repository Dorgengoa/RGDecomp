#include "types.h"

extern s32 StrNotEqual_1f5300(void *, void *);

typedef struct Ent { u8 pad0[4]; s8 *name; u8 pad8[0xC]; } Ent;
typedef struct Grp { u8 pad0[0x1C]; s32 n; Ent *ents; u8 pad24[4]; } Grp;

static inline u8 neq(s8 *s, s8 *t)
{
    u8 f = 1;
    if (*s == *t && StrNotEqual_1f5300(s + 1, t + 1) == 0) {
        f = 0;
    }
    return f;
}

typedef struct Obj { u8 pad0[0x7C]; s16 count; u8 pad7e[0x8C - 0x7E]; Grp *grps; } Obj;

Ent *TableFindByNameGrouped_415d10(Obj *arg0, s8 *arg1) {
    Grp *g;
    s32 i;
    Ent *e;
    s32 j;
    g = arg0->grps;
    if (g == NULL || arg0->count <= 0) return NULL;
    for (i = 0; i < arg0->count; i++, g++) {
        e = g->ents;
        for (j = 0; j < g->n; j++, e++) {
            if (neq(e->name, arg1) == 0) {
                return e;
            }
        }
    }
    return NULL;
}
