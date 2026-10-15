#include "types.h"

extern void *HpGaugeDtor_31e240(void *, s16);
extern void OperatorDelete_100840(void *);

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
