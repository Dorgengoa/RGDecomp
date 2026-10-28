/* rgp:protos */
#define RGP_SELF_BgmGetResumeWaitChan_207e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data s16 D_00481C90. */

extern s16 D_00481C90;

s16 BgmGetResumeWaitChan_207e90(void)
{
    return D_00481C90;
}
