/* rgp:protos */
#define RGP_SELF_NavMgrGetCurrent_30cab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T30CAB0 { u8 pad000[0x28]; s32 f28; };

/*rgp*/

s32 NavMgrGetCurrent_30cab0(struct T30CAB0 *p)
{
    s32 v;

    v = p->f28;
    if (v == 0) {
        return 0;
    }
    return NavMgrFindGraphById_30cae0(p, v);
}
