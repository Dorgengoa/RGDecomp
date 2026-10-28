/* rgp:protos */
#define RGP_SELF_DrawScreenFillRect_38a4b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawScreenFillRect_38a4b0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ScreenGetWidth_390d10();
    r1 = ScreenGetHeight_390ce0();
    DrawColorRect_1cc040(0, 0, r0, r1, p0);
}
