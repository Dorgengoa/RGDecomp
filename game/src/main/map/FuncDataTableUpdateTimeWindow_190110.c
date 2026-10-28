/* rgp:protos */
#define RGP_SELF_FuncDataTableUpdateTimeWindow_190110 1
#define RGP_SELF_chk190b 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#pragma auto_inline on
#pragma inline_max_size(10000)
#pragma inline_max_auto_size(10000)
#pragma inline_depth(3)
#pragma opt_loop_invariants off

typedef struct O190 {
    u8  pad000[0x44];
    s32 m44;
    s32 m48;
    u8  pad04C[0xC];
    f32 m58;
    f32 m5C;
} O190;

typedef struct N190 {
    struct N190 *next;
    u8  pad004[0xC];
    O190 *obj;
} N190;

typedef struct P190 {
    u8  pad000[0x4];
    N190 **m4;
    N190 *m8;
} P190;

static inline s32 chk190b(O190 *cur, f32 *v)
{
    f32 hi;
    f32 lo;
    f32 val;

    hi = cur->m5C;
    lo = cur->m58;
    val = *v;
    if (hi > lo) {
        if (val < lo) {
            return 0;
        } else {
            if (val >= hi) {
                return 0;
            } else {
                return 1;
            }
        }
    } else {
        if (lo > hi) {
            if (val >= lo) {
                return 1;
            } else {
                if (val < hi) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } else {
            return 1;
        }
    }
}

s32 FuncDataTableUpdateTimeWindow_190110(P190 *p, s32 i, f32 *v)
{
    N190 **t;
    N190 *e;
    O190 *cur;
    s32 count;
    s32 res;
    f32 hi;
    f32 lo;
    f32 val;

    p->m8 = 0;
    t = p->m4;
    if (t != 0) {
        if (i >= 0 && i < 11) {
            p->m8 = t[i];
        }
    }
    count = 0;
    while (e = p->m8, e == 0 ? (cur = 0) : (p->m8 = e->next, cur = e->obj), cur != 0) {
        res = cur->m44;
        if (res == 0) {
            res = 0;
        } else if (v == 0) {
            res = 1;
        } else {
            res = chk190b(cur, v);
        }
        cur->m48 = res;
        if (res != 0) {
            count++;
        }
    }
    p->m8 = 0;
    return count;
}
