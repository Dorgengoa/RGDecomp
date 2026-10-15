#include "types.h"

extern s32 strcmp(s8 *a, s8 *b);

typedef struct { s8 *name; s32 unk4; s32 unk8; s32 unkC; } E1965c0;
typedef struct { s32 count; s32 pad[3]; E1965c0 e[1]; } T1965c0;

static inline E1965c0 *find(T1965c0 *t, s8 *name) {
    s32 i;
    E1965c0 *e;
    if (name == NULL) return NULL;
    for (i = 0; i < t->count; i++) {
        e = &t->e[i];
        if (e->name != NULL && strcmp(e->name, name) == 0) return e;
    }
    return NULL;
}
s32 SceneTableRemoveModelCfg_1965c0(T1965c0 *arg0, s8 *arg1)
{
    E1965c0 *e = find(arg0, arg1);
    if (e == NULL) {
        return 0;
    }
    e->name = NULL;
    e->unk4 = 0;
    e->unk8 = 0;
    return 1;
}
