#include "types.h"

extern const u8 D_0046FF20[];
extern const u8 D_0046FEE0[];
extern void OperatorDelete_100840(void *);

void *FilebufDtor_102e80(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)((u8 *)o + 0x0) = D_0046FF20;
        if (o != 0) {
            *(const u8 **)((u8 *)o + 0x0) = D_0046FEE0;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
