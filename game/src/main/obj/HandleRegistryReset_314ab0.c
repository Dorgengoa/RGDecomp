/* rgp:protos */
#define RGP_SELF_HandleRegistryReset_314ab0 1
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
    u8 pad000[0x4];
    s32 m04;
};

void HandleRegistryReset_314ab0(struct Obj0 *p0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    p0->m04 = 0;
    HandleRegistryClear_314790(p0, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
}
