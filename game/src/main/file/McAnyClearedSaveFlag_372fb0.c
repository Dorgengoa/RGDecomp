/* rgp:protos */
#define RGP_SELF_McAnyClearedSaveFlag_372fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00483168;
extern u8 D_00483169;

s32 McAnyClearedSaveFlag_372fb0(void)
{
    return D_00483168 != 0 || D_00483169 != 0;
}
