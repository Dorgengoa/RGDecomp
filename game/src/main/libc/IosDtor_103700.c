/* rgp:protos */
#define RGP_SELF_IosDtor_103700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FEA8[];
extern void *IosBaseDtor_102970(void *, s16);
/*rgp*/

void *IosDtor_103700(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FEA8;
        IosBaseDtor_102970(o, 0);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
