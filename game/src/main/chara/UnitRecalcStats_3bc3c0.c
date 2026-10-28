/* rgp:protos */
#define RGP_SELF_UnitRecalcStats_3bc3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

u32 UnitRecalcStats_3bc3c0(void *a)
{
    UnitResetStatsToBaseThunk_3bc460(a);
    return (u8)(((unsigned char)UnitApplyStatusStatModsThunk_3bc440(a)));
}
