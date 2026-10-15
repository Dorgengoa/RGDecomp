#include "types.h"

extern void HpGaugeDisable_31d410(void *);
extern void *HpGaugeBaseDtor_31ea50(void *, s16);
extern void OperatorDelete_100840(void *);

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
