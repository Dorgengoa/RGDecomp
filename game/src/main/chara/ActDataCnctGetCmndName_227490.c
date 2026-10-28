/* rgp:protos */
#define RGP_SELF_ActDataCnctGetCmndName_227490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 ActDataCnctGetCmndName_227490(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;

    t0 = p0->m00;
    if (t0 != 0) {
        r0 = ActInfoCmndGetName_231210(t0);
        return r0;
    }
    return 0;
}
