#include "types.h"

typedef struct E {
    u8 pad[6];
    s16 x6;
    u8 pad8[2];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 padB[5];
    s16 *x10;
} E;

extern u32 InvGetCategoryOfId_3d56f0(s16);
extern E *PoolGetUsedElem_36acb0(void *, s32);
extern s32 InvCategoryMatches_3c8720(u8 *, s32, u32);
extern s32 D_00465B50[];

s32 InvHasItemInCategory_3c7f40(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 n;
    s32 i;
    E *e;

    if (*(void **)(arg0 + 0x168) == NULL) {
        return 0;
    }
    n = D_00465B50[0];
    for (i = 0; i < n; i++) {
        e = PoolGetUsedElem_36acb0(*(void **)(arg0 + 0x168), i);
        if (e != NULL && (arg3 != 0 || !e->f1) && InvCategoryMatches_3c8720(arg0, arg2, InvGetCategoryOfId_3d56f0(e->x6)) != 0 && arg1 == *e->x10) {
            return 1;
        }
    }
    return 0;
}
