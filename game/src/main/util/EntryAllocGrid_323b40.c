/* rgp:protos */
#define RGP_SELF_EntryAllocGrid_323b40 1
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
    s32 m00;
};

s32 EntryAllocGrid_323b40(struct Obj0 *p0, s32 p1)
{
    s32 v3C;
    s32 v38;
    s32 t0;
    s32 t1;
    s32 r1;

    EntryGetGridSize_323bb0(p0, &v3C, &v38);
    t0 = v3C;
    t1 = v38;
    if ((t0 * t1) > 0) {
        r1 = ((s32)MemStackNew_14e1b0(((t0 * t1) * 3), p1));
        p0->m00 = r1;
        return 1;
    }
    return 0;
}
