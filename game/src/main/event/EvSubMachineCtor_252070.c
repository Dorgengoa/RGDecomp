/* rgp:protos */
#define RGP_SELF_EvSubMachineCtor_252070 1
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
    s32 m04;
};

void EvSubMachineCtor_252070(struct Obj0 *p0)
{
    p0->m00 = 0;
    p0->m04 = 0;
    EvSubMachineInit_251ff0(p0, 0, 0);
}
