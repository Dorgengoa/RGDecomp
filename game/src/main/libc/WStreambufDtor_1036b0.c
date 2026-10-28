/* rgp:protos */
#define RGP_SELF_WStreambufDtor_1036b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FE10[];
/*rgp*/

void *WStreambufDtor_1036b0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FE10;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
