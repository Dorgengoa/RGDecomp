#include "types.h"

/* Record the pending value on the owner, then notify the listener.  The
   `sw $7` sits in a branch-likely slot because mwcc duplicated the store
   from the fall-through block, not because it is conditional.

   Clone of WorldSubsysLoad_3f9310: this group varies only in the flag global and the
   two field offsets. */

class VB {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    s32 v5(void * a0, s32 a1, s32 a2) { return VCM(s32, (void *, void *, s32, s32), 0x1C, a0, a1, a2); }
};

typedef struct Owner00410b00 {
    s32   m00;
    s32   m04;
    s32   m08;
    VB   *m0C;
} Owner00410b00;

/* Wider than four bytes so mwcc gives it %hi/%lo instead of a $gp load --
   the same reason the accessor units in src/accessors spell it this way. */
extern "C" struct rgp_anon_D_00465838 { s32 v; u8 pad[0xC]; } D_00465838;

extern "C" s32 WorldSubsysPurposeLoad_410b00(Owner00410b00 *o, void *p, s32 unused, s32 v)
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
        l->v5(p, D_00465838.v != 0, 0);
    }
    return 1;
}
