/* rgp:protos */
#define RGP_SELF_HelpBoardIsFileLoaded_34dc60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047F6E4;

u8 HelpBoardIsFileLoaded_34dc60(void)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    r1 = LoaderGetStatus_1cd4f0(r0, D_0047F6E4);
    return (r1 == 1);
}
