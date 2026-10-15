#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 base;
    s32 x4;
    s32 n8;
    s32 nC;
    s32 n10;
    s32 n14;
    s32 n18;
    u8 pad1C[0x24];
    s32 sema;
} R;

extern void SignalSema(s32);
extern void WaitSema(s32);

void ViBufBeginPut_1d44b0(R *r, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 a;
    s32 b;
    s32 m;
    s32 k;

    WaitSema(r->sema);
    b = r->n14;
    a = r->n10;
    { s32 s = (r->nC + a) << 11; m = (s + b) % r->n18; }
    k = (((r->n8 - 2) - a) << 11) - b;
    if (r->n18 - m >= k) {
        *arg1 = r->base + m;
        *arg2 = k;
        *arg3 = 0;
        *arg4 = 0;
    } else {
        *arg1 = r->base + m;
        *arg2 = r->n18 - m;
        *arg3 = r->base;
        *arg4 = k - (r->n18 - m);
    }
    SignalSema(r->sema);
}
