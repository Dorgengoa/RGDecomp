/* rgp:protos */
#define RGP_SELF_InsectTeamTableInit_431da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

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
        r1 = ((s32)MemStackNew_14e130(0x1588, p1));
        p0->m1188 = r1;
        rv2 = 1;
    }
    return rv2;
}
