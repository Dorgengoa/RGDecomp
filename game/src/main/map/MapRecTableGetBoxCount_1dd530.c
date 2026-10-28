/* rgp:protos */
#define RGP_SELF_MapRecTableGetBoxCount_1dd530 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x3E];
    s16 m3E;
};

s16 MapRecTableGetBoxCount_1dd530(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m3E;
    return t0;
}
