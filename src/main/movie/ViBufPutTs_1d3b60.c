#include "types.h"

/* MAIN ViBufPutTs_1d3b60 -- guarded ring-buffer enqueue behind a semaphore.
   The four writes each RE-READ q->m5C and q->m50: repeated stores through a
   struct pointer are SEPARATE statements, mwcc does no DSE there.
   divbyzerocheck supplies the `% q->m54` trap. */

#pragma divbyzerocheck on

typedef struct Item1D3B60 {
    s64 m00;
    s64 m08;
    s32 m10;
    s32 m14;
} Item1D3B60;

typedef struct Q1D3B60 {
    u8 pad00[0x40];
    s32 m40;
    u8 pad44[0xC];
    Item1D3B60 *m50;
    s32 m54;
    s32 m58;
    s32 m5C;
} Q1D3B60;

extern void WaitSema(s32);
extern void SignalSema(s32);
extern void ViBufModifyPts_1d3ca0(Q1D3B60 *, Item1D3B60 *);

s32 ViBufPutTs_1d3b60(Q1D3B60 *q, Item1D3B60 *it)
{
    s32 ok;

    ok = 0;
    WaitSema(q->m40);
    if (q->m58 < q->m54) {
        ViBufModifyPts_1d3ca0(q, it);
        if (it->m00 >= 0 || it->m08 >= 0) {
            q->m50[q->m5C].m00 = it->m00;
            q->m50[q->m5C].m08 = it->m08;
            q->m50[q->m5C].m10 = it->m10;
            q->m50[q->m5C].m14 = it->m14;
            q->m58 = q->m58 + 1;
            q->m5C = (q->m5C + 1) % q->m54;
        }
        ok = 1;
    }
    SignalSema(q->m40);
    return ok;
}
