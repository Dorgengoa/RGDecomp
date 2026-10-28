/* rgp:protos */
#define RGP_SELF_NavGraphDtor_30d5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_00471A50[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *NavGraphDtor_30d5c0(void *o, s16 flag)
{
    void *q;

    if (o != 0) {
        q = (u8 *)o + 0x90;
        if (q != 0) {
            *(const u8 **)((u8 *)o + 0x9C) = D_00471A50;
            NavGraphStrPoolDtor_30d7d0((u8 *)o + 0xD0, -1);
            NavGraphEdgeIdxPoolDtor_30d760((u8 *)o + 0xC0, -1);
            NavGraphEdgePoolDtor_30d6e0((u8 *)o + 0xB0, -1);
            NavGraphNodePoolDtor_30d660((u8 *)o + 0xA0, -1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
