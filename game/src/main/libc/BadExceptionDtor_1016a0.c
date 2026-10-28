/* rgp:protos */
#define RGP_SELF_BadExceptionDtor_1016a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FD90[];
extern u8 D_0046FD70[];
/*rgp*/

void *BadExceptionDtor_1016a0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)((u8 *)o + 0x0) = D_0046FD90;
        if (o != 0) {
            *(const u8 **)((u8 *)o + 0x0) = D_0046FD70;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
