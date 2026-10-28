/* rgp:protos */
#define RGP_SELF_HpGaugeObjDtor_31d160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void *HpGaugeObjDtor_31d160(void *o, s16 flag)
{
    if (o != 0) {
        HpGaugeDtor_31e240(o, 0);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
