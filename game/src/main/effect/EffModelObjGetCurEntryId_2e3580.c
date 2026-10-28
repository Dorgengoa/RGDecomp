/* rgp:protos */
#define RGP_SELF_EffModelObjGetCurEntryId_2e3580 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x9C8];
    s16 m9C8;
};

s32 EffModelObjGetCurEntryId_2e3580(struct Obj0 *p0)
{
    s16 t0;

    t0 = p0->m9C8;
    return (s16)(t0);
}
