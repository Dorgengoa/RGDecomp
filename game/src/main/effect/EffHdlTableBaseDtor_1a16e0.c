/* rgp:protos */
#define RGP_SELF_EffHdlTableBaseDtor_1a16e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void *EffHdlTableBaseDtor_1a16e0(void *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            StrVectorDtor_1a21a0(o, 0);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
