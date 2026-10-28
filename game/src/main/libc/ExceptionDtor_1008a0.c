/* rgp:protos */
#define RGP_SELF_ExceptionDtor_1008a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FD70[];
/*rgp*/

void *ExceptionDtor_1008a0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FD70;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
