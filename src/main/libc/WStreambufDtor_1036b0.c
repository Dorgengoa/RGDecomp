#include "types.h"

extern const u8 D_0046FE10[];
extern void OperatorDelete_100840(void *);

void *WStreambufDtor_1036b0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FE10;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
