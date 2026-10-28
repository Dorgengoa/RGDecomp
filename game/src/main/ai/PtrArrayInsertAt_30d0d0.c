/* rgp:protos */
#define RGP_SELF_PtrArrayInsertAt_30d0d0 1
#define RGP_SELF_ins 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct {
    s32 *arr;
    u32 count;
    u32 cap;
    u32 pow;
} Vec_30d0d0;

static inline s32 ins(Vec_30d0d0 *v, s32 item, u32 idx)
{
    s32 i;
    if (item == 0) {
        return -1;
    }
    if (v->count < idx) {
        return -1;
    }
    if (v->cap <= v->count) {
        return -1;
    }
    for (i = v->count - 1; i >= (s32)idx; i--) {
        s32 *a = v->arr;
        a[i + 1] = a[i];
    }
    v->arr[idx] = item;
    v->count++;
    return idx;
}

s32 PtrArrayInsertAt_30d0d0(Vec_30d0d0 *arg0, s32 arg1, u32 arg2) {
    s32 r;

    r = ins(arg0, arg1, arg2);
    if (r < 0) {
        return -1;
    }
    for (arg0->pow = 1; arg0->pow < arg0->count; arg0->pow *= 2) {
    }
    return r;
}
