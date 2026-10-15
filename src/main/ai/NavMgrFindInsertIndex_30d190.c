#include "types.h"

extern s32 IntCompare_42ca30(s32 arg0, s32 arg1);
extern s32 NavGraphGetIdThunk_310e90(s32 arg0);

typedef struct {
    s32 *data;
    u32 n;
    u8 pad8[0x4];
    s32 unkC;
} T30d190_arg0;

static inline s32 get30d190(T30d190_arg0 *a, u32 i)
{
    if (i >= a->n) {
        return 0;
    }
    return a->data[i];
}

s32 NavMgrFindInsertIndex_30d190(T30d190_arg0 *arg0, s32 arg1)
{
    s32 lo;
    s32 step;
    u32 mid;

    if (arg0->n == 0) {
        return 0;
    }
    if (IntCompare_42ca30(arg1, NavGraphGetIdThunk_310e90(get30d190(arg0, 0))) < 0) {
        return 0;
    }
    step = arg0->unkC;
    lo = 0;
    while (step > 0) {
        step >>= 1;
        mid = lo + step;
        if (mid < arg0->n) {
            if (IntCompare_42ca30(arg1, NavGraphGetIdThunk_310e90(arg0->data[mid])) >= 0) {
                lo += step;
            }
        }
    }
    return lo + 1;
}
