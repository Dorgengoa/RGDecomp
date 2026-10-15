#include "types.h"

typedef struct { s32 *list; s32 pad4; s16 max; s16 min; s16 cnt; s16 n; } S1ddaf0;
extern u32 MapDataGetId_1e7bd0(s32 arg0);

s32 MapIdIndexFind_1ddaf0(S1ddaf0 *a, s32 key)
{
    s32 half;
    s32 lo;
    s32 idx;
    s32 e;

    if (key < a->min || key > a->max) return 0;
    half = a->cnt;
    lo = 0;
    do {
        half >>= 1;
        idx = lo + half;
        if (idx < a->n) {
            e = a->list[idx];
            if (MapDataGetId_1e7bd0(e) == key) return e;
            if (MapDataGetId_1e7bd0(e) < (u32)key) lo += half;
        }
    } while (half > 0);
    return 0;
}
