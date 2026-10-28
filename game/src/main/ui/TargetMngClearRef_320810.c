/* rgp:protos */
#define RGP_SELF_TargetMngClearRef_320810 1
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

void TargetMngClearRef_320810(struct Obj0 *p0)
{
    p0->m00 = 0;
    TargetRefClear_2e71d0((struct Obj0 *)((u8 *)p0 + 0xC0));
}
