/* rgp:protos */
#define RGP_SELF_EvMapObjPartClear_3641f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void EvMapObjPartClear_3641f0(u8 *o)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        EvMapObjPointReset_3644f0(o + i * 0x40);
    }
    *(s32 *)(o + 0x138) = 0;
}
