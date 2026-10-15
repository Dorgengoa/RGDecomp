#include "types.h"
#pragma opt_repositioncode off
extern s32 Strcasecmp_1345b8(s8 *, s32);

void *ObjListFindByName_189500(u8 *arg0, s8 *arg1, s32 *arg2)
{
    s32 i;
    u8 *p;
    s32 t;

    if (arg1 == NULL || *arg1 == 0) {
        return NULL;
    }
    for (i = 0; i < 7; i++) {
            for (p = *(u8 **)(arg0 + i * 4 + 0x284); p != NULL; p = *(u8 **)p) {
                t = *(s32 *)(p + 0x10);
                if (t != 0 && t + 0x6C != 0 && Strcasecmp_1345b8(arg1, t + 0x6C) == 0) {
                    if (arg2 != NULL) {
                        *arg2 = i;
                    }
                    return p;
                }
            }
    }
    return NULL;
}
