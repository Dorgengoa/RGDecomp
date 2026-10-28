/* rgp:protos */
#define RGP_SELF_CharaRecalcStats_3a93e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

u32 CharaRecalcStats_3a93e0(void *p)
{
    CharaResetStatsToBaseThunk_3a9480(p);
    return (u8)((u8)((unsigned char)CharaApplyStatModsThunk_3a9460(p)));
}
