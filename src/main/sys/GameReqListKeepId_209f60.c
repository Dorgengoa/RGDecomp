#include "types.h"
#pragma opt_common_subs off

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V00209f60;

typedef struct {
    s32 a;
    s32 b;
    V00209f60 v;
} E00209f60;

typedef struct {
    E00209f60 *list;
    s16 count;
} H00209f60;

void GameReqListKeepId_209f60(H00209f60 *arg0, s32 arg1)
{
    E00209f60 *src;
    E00209f60 *dst;
    s32 count;
    s32 i;
    s32 t;

    src = arg0->list;
    if (src == NULL || arg0->count <= 0) {
        return;
    }
    dst = src;
    count = 0;
    for (i = 0; i < arg0->count; i++, src++) {
        t = src->a;
        if ((t == arg1) || ((u32)(t - 2) < 2U)) {
            if (dst != src) {
                dst->a = src->a;
                dst->b = src->b;
                dst->v = src->v;
            }
            dst++;
            count++;
        }
    }
    arg0->count = count;
}
