/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuGetResult_4f9d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F9D50 -- `jr $31 / lh $2, -0xD0C($28)`.  A signed halfword read
 * from small data, returned.  One of the 55 unnamed functions. */
extern s16 D_00484464;

s32 normal_BtlChgMenuGetResult_4f9d50(void)
{
    return D_00484464;
}
