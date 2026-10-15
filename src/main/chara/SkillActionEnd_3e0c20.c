#include "types.h"

extern void * SkillActionFindById_3e0ee0(s32);
extern s32 SkillActionReset_3e3dd0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 SkillActionEnd_3e0c20(s32 p0)
{
    struct Obj0 *r0;
    s32 rv3;
    s16 t0;
    s32 rv2;
    s32 r1;

    r0 = SkillActionFindById_3e0ee0(p0);
    rv3 = rv2;
    if (r0 == 0) {
        rv3 = 0;
    } else {
        t0 = r0->m00;
        rv2 = 1;
        if (t0 < 0) {
            rv2 = 0;
        } else {
            r1 = SkillActionReset_3e3dd0(r0);
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
