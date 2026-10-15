#include "types.h"

extern const u8 D_0046FD70[];
extern void OperatorDelete_100840(void *);

void *ExceptionDtor_1008a0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FD70;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
