#include "types.h"

/* Latch the pending value on the owner and notify BOTH listeners.  The
   second call reloads $5 because the first clobbered it; the first inherits
   the incoming argument untouched, which is why only one of the two call
   sites materialises it.

   Clone of WorldSubsysLoad_402590: this group varies only in the two flag globals and
   the three field offsets. */

class VB {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual s32 v5(void *, s32, s32);
};

typedef struct Owner003f43b0 {
    s32   m00;
    s32   m04;
    VB   *m08;
    u8    pad00C[4];
    VB   *m10;
} Owner003f43b0;

/* Wider than four bytes so mwcc gives these %hi/%lo instead of a $gp load. */
extern struct { s32 v; u8 pad[0xC]; } D_004657D0;
extern struct { s32 v; u8 pad[0xC]; } D_004657E0;

extern "C" s32 WorldSubsysLoad_402590(Owner003f43b0 *o, void *p, s32 unused, s32 v)
{
    VB *l1;
    VB *l2;

    if (p == 0) {
        return 0;
    }
    if (o->m00 == 0) {
        return 0;
    }
    o->m04 = v;
    l1 = o->m08;
    if (l1 != 0) {
        l1->v5(p, D_004657D0.v != 0, 0);
    }
    l2 = o->m10;
    if (l2 != 0) {
        l2->v5(p, D_004657E0.v != 0, 0);
    }
    return 1;
}
