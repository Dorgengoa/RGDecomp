/* rgp:protos */
#define RGP_SELF_SeventhMysteryCursorMoveCb_394a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SeventhMysteryCursorMoveCb_394a50(s32 p0)
{
    s32 r1;

    PlayMenuSe_289ef0(4);
    r1 = SeventhMysteryCursorPlace_3948a0(p0);
    return 1;
}
