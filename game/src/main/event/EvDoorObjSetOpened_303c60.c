/* rgp:protos */
#define RGP_SELF_EvDoorObjSetOpened_303c60 1
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
    u8 pad000[0x19E];
    s16 m19E;
};

void EvDoorObjSetOpened_303c60(struct Obj0 *p0, s32 p1)
{
    EvDoorObjPlayOpen_303c90(p0, p1);
    p0->m19E = 0x7FFF;
}
