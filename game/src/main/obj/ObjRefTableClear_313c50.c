/* rgp:protos */
#define RGP_SELF_ObjRefTableClear_313c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482A38;

void ObjRefTableClear_313c50(int rgp_a0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    HandleRegistryClear_314790(&D_00482A38, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
}
