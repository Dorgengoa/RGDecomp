/* rgp:protos */
#define RGP_SELF_BadAllocDtor_100920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FD80[];
extern u8 D_0046FD70[];
/*rgp*/

void *BadAllocDtor_100920(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)((u8 *)o + 0x0) = D_0046FD80;
        if (o != 0) {
            *(const u8 **)((u8 *)o + 0x0) = D_0046FD70;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
