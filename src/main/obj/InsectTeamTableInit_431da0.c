#include "types.h"

extern void InsectTeamTableClear_431e00(void *);
extern s32 MemStackNew_14e130(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1188];
    s32 m1188;
};

s32 InsectTeamTableInit_431da0(struct Obj0 *p0, s32 p1)
{
    s32 rv2;
    s32 r1;

    rv2 = 1;
    if (p1 == 0) {
        rv2 = 0;
    } else {
        InsectTeamTableClear_431e00(p0);
        r1 = MemStackNew_14e130(0x1588, p1);
        p0->m1188 = r1;
        rv2 = 1;
    }
    return rv2;
}
