#include "types.h"

extern const u8 D_0046FD90[];
extern const u8 D_0046FD70[];
extern void OperatorDelete_100840(void *);

void *BadExceptionDtor_1016a0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)((u8 *)o + 0x0) = D_0046FD90;
        if (o != 0) {
            *(const u8 **)((u8 *)o + 0x0) = D_0046FD70;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
