/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageIsActive_506000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506000 -- `not $2,$2 / sltu $2,$0,$2` is `!= -1`. */
/*rgp*/

s32 normal_BtlChgPageIsActive_506000(void *p)
{
    return normal_BtlChgPageGetStateId_5061a0(p) != -1;
}
