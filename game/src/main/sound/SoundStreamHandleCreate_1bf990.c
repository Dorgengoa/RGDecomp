/* rgp:protos */
#define RGP_SELF_SoundStreamHandleCreate_1bf990 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef union { s32 w; struct { u16 lo; u16 hi; } s; } H1bf990;
typedef struct { u8 d[0x82]; u16 gen; } E1bf990;
typedef struct { u32 count; E1bf990 e[1]; } T1bf990;
/*rgp*/
/*rgp*/

static inline E1bf990 *get(T1bf990 *t, s32 hv) {
    H1bf990 h __attribute__((aligned(16)));
    s32 hi;
    s32 lo;
    E1bf990 *r;
    h.w = hv;
    hi = h.s.hi;
    lo = h.s.lo;
    if (hi == 0 || lo >= t->count) {
        r = 0;
    } else if (t->e[lo].gen != hi) {
        r = 0;
    } else {
        r = &t->e[lo];
    }
    return r;
}

#pragma opt_propagation off
void SoundStreamHandleCreate_1bf990(s32 *arg0, T1bf990 *arg1, s32 arg2, s32 arg3)
{
    s32 h;
    E1bf990 *e;

    SoundStreamHandleAlloc_1bfba0(&h, (void *)arg1);
    e = get(arg1, h);
    if (e == 0) {
        ((u16 *)arg0)[0] = 0;
        ((u16 *)arg0)[1] = 0;
        return;
    }
    SoundStreamInit_1c0ea0(e, arg2, arg3);
    *arg0 = h;
}
