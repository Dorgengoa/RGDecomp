#include "types.h"

/* Record the pending value on the owner, then notify the listener.  The
   `sw $7` sits in a branch-likely slot because mwcc duplicated the store
   from the fall-through block, not because it is conditional.

   Clone of WorldSubsysPurposeLoad_424610: this group varies only in the flag global and the
   two field offsets. */

class VB {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual s32 v5(void *, s32, s32);
};

typedef struct Owner003f9310 {
    s32   m00;
    u8    pad004[4];
    s32   m08;
    VB   *m0C;
} Owner003f9310;

/* Wider than four bytes so mwcc gives it %hi/%lo instead of a $gp load --
   the same reason the accessor units in src/accessors spell it this way. */
extern struct { s32 v; u8 pad[0xC]; } D_004658A0;

extern "C" s32 WorldSubsysPurposeLoad_424610(Owner003f9310 *o, void *p, s32 unused, s32 v)
{
    VB *l;

    if (p == 0) {
        return 0;
    }
    if (o->m00 == 0) {
        return 0;
    }
    o->m08 = v;
    l = o->m0C;
    if (l != 0) {
        l->v5(p, D_004658A0.v != 0, 0);
    }
    return 1;
}
