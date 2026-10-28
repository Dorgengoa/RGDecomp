/* rgp:protos */
#define RGP_SELF_HpGaugeDtor_31e240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void *HpGaugeDtor_31e240(void *o, s16 flag)
{
    if (o != 0) {
        HpGaugeDisable_31d410(o);
        HpGaugeBaseDtor_31ea50(o, -1);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
