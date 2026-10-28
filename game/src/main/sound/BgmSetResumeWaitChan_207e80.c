/* rgp:protos */
#define RGP_SELF_BgmSetResumeWaitChan_207e80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s16 D_00481C90.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s16 D_00481C90;

void BgmSetResumeWaitChan_207e80(s16 value)
{
    D_00481C90 = value;
}
