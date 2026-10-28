/* rgp:protos */
#define RGP_SELF_SeventhMysteryResRequest_395660 1
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

extern s32 D_0047FF28;
extern s32 D_0047FF2C;
extern s32 D_004802B8;

s32 SeventhMysteryResRequest_395660(void)
{
    s32 r0;
    s32 t0;
    s32 r1;
    s32 r2;

    r0 = ((s32)GetLoaderMgr_1f59d0());
    t0 = D_004802B8;
    D_0047FF28 = -1;
    D_0047FF2C = 0;
    r1 = LoaderRequestFile_1cd870(r0, t0, 0);
    D_0047FF28 = r1;
    if (r1 == -1) {
        return 1;
    }
    r2 = LoaderQueueAppendSeparator_1cd670(r0);
    return 0;
}
