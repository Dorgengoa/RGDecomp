#include "types.h"

extern s32 GroupFindByKey_411620(s32, s32);
extern s32 GroupSubEntryRange_412800(s32, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 GroupGetSubEntryRange_4112f0(s32 p0, s32 p1, s32 p2, struct Obj0 *p3)
{
    s32 r0;
    s32 r1;

    p3->m00 = 0;
    r0 = GroupFindByKey_411620(p0, p1);
    if (r0 != 0) {
        r1 = GroupSubEntryRange_412800(r0, p2, p3);
        return r1;
    }
    return 0;
}
