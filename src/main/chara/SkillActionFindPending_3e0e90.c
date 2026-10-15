#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E9770[];

struct Obj0;

struct Obj0 {
    s16 m00;
    u8 pad002[0x3E];
    u8 m40;
};

s32 SkillActionFindPending_3e0e90(void)
{
    struct Obj0 *l0;
    s32 l1;
    s16 t0;
    u8 t1;

    l0 = (struct Obj0 *)D_004E9770;
    l1 = 0;
    while (l1 < 2) {
        t0 = l0->m00;
        if (t0 >= 0) {
            t1 = l0->m40;
            if ((t1 & 1) == 0) {
                return (s32)l0;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj0 *)((u8 *)l0 + 0x48);
    }
    return 0;
}
