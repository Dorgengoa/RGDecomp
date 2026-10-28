/* rgp:protos */
#define RGP_SELF_MinimapMgrDtor_3223f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void *MinimapMgrDtor_3223f0(void *o, s16 flag)
{
    if (o != 0) {
        DestroyArray_1005b0(o, (void *)MinimapSlotDtor_3225c0, 0x1B0, 3);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
