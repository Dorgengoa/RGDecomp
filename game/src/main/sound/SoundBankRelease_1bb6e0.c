/* rgp:protos */
#define RGP_SELF_SoundBankRelease_1bb6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of AreaBoxInit_1e01f0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

void SoundBankRelease_1bb6e0(s32 p0)
{
    SoundBankStopAll_1bad70((int)p0);
    SoundBankFree_1b9c00(p0);
}
