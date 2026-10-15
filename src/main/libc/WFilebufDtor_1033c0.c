#include "types.h"

extern const u8 D_0046FE50[];
extern const u8 D_0046FE10[];
extern void OperatorDelete_100840(void *);

void *WFilebufDtor_1033c0(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)((u8 *)o + 0x0) = D_0046FE50;
        if (o != 0) {
            *(const u8 **)((u8 *)o + 0x0) = D_0046FE10;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
