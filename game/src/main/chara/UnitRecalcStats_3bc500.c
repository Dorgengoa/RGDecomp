/* rgp:protos */
#define RGP_SELF_UnitRecalcStats_3bc500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

u32 UnitRecalcStats_3bc500(void *a)
{
    UnitResetStatsToBaseThunk_3bc5a0(a);
    return (u8)(((unsigned char)UnitApplyStatusStatModsThunk_3bc580(a)));
}
