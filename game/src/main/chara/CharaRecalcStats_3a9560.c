/* rgp:protos */
#define RGP_SELF_CharaRecalcStats_3a9560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

u32 CharaRecalcStats_3a9560(void *a)
{
    CharaResetStatsToBaseThunk_3a9600(a);
    return (u8)(((unsigned char)CharaApplyStatModsThunk_3a95e0(a)));
}
