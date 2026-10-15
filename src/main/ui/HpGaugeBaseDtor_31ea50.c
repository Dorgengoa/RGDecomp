#include "types.h"

extern void *HpGaugeClearSlotsThunk_31e9c0(void *);
extern void OperatorDelete_100840(void *);

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
