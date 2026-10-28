/* rgp:protos */
#define RGP_SELF_EvObjIsTargetActive_2f9a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2F9A20 { u8 pad000[0xD0]; u32 fD0; };

/*rgp*/

s32 EvObjIsTargetActive_2f9a20(struct T2F9A20 *p)
{
    if ((p->fD0 & 0x80000000) != 0) {
        return 0;
    }
    return TargetRefIsActive_2e6f00((u8 *)p + 0xA0);
}
