/* rgp:protos */
#define RGP_SELF_ObjRecCollectLiveObjects_1c5150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 ObjRecCollectLiveObjects_1c5150(void *arg0, s32 *arg1, s32 arg2)
{
    s32 i;
    s32 j;

    i = 0;
    j = 0;
    while (i < *(s32 *)((u8 *)arg0 + 0x3C58)) {
        if (j >= arg2) {
            break;
        }
        if (((unsigned char)ObjRecHasFlags6_1c3eb0(arg0, 2, i)) != 0) {
            arg1[j] = ((s32)ObjRecGetLiveObject_1c5250(arg0, i));
            j++;
        }
        i++;
    }
    return j;
}
