/* rgp:protos */
#define RGP_SELF_HpGaugeBaseDtor_31ea50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void *HpGaugeBaseDtor_31ea50(void *o, s16 flag)
{
    if (o != 0) {
        HpGaugeClearSlotsThunk_31e9c0(o);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
