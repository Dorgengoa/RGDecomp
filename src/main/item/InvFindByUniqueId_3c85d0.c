#include "types.h"

typedef struct E3c85d0 {
    u8 pad0[4];
    s16 m4;
    s16 m6;
    u8 pad8[2];
    u8 mA;
} E3c85d0;

extern E3c85d0 *PoolGetUsedElem_36acb0(s32, s32);
struct A3c85d0;
extern s32 InvCategoryMatches_3c8720(struct A3c85d0 *, s32, s32);
extern s32 InvGetCategoryOfId_3d56f0(s32);
extern const s32 D_00465B50[0x100];

typedef struct A3c85d0 { u8 pad[0x168]; s32 m168; } A3c85d0;

E3c85d0 *InvFindByUniqueId_3c85d0(A3c85d0 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    E3c85d0 *found;
    s32 i;
    E3c85d0 *e;

    if (arg1 < 0) {
        return NULL;
    }
    if (arg0->m168 == 0) {
        return NULL;
    }
    found = NULL;
    for (i = 0; i < D_00465B50[0]; i++) {
        e = PoolGetUsedElem_36acb0(arg0->m168, i);
        if (e == NULL) {
            continue;
        }
        if (arg3 == 0 && ((u64)((u64)e->mA << 62) >> 63) != 0) {
            continue;
        }
        if (InvCategoryMatches_3c8720(arg0, arg2, InvGetCategoryOfId_3d56f0(e->m6)) == 0) {
            continue;
        }
        if (arg1 != e->m4) {
            continue;
        }
        found = e;
        break;
    }
    return found;
}
