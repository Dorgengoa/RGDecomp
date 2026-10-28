/* rgp:protos */
#define RGP_SELF_MinimapSubReset_32af90 1
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
    u8 pad000[0x8];
    s16 m08;
};

void MinimapSubReset_32af90(struct Obj0 *p0)
{
    p0->m08 = 0;
    MinimapSubSetCapacity_32aea0(p0, 0);
    MinimapSubSetHeap_32af80(p0, 0);
}
