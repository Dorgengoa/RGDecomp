/* rgp:protos */
#define RGP_SELF_McStateReset_372f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048316C;
extern s32 D_00483170;
extern s32 D_00483174;
extern s16 D_00483180;
extern u8 D_00483184;

void McStateReset_372f80(void)
{
    D_0048316C = 0;
    D_00483170 = 0;
    D_00483184 = 0;
    D_00483174 = 0;
    D_00483180 = 0;
}
