/* rgp:protos */
#define RGP_SELF_UnitRecalcStats_3bc640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

u32 UnitRecalcStats_3bc640(void *a)
{
    UnitResetStatsToBaseThunk_3bc6e0(a);
    return (u8)(((unsigned char)UnitApplyStatusStatModsThunk_3bc6c0(a)));
}
