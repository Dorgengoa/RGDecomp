/* rgp:protos */
#define RGP_SELF_StreambufDtor_103760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0046FEE0[];
/*rgp*/

void *StreambufDtor_103760(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FEE0;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
