#include "types.h"

extern const u8 D_0046FDD8[];
extern void *IosBaseDtor_102970(void *, s16);
extern void OperatorDelete_100840(void *);

void *WiosDtor_103650(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FDD8;
        IosBaseDtor_102970(o, 0);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
