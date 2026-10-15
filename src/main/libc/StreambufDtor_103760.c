#include "types.h"

extern const u8 D_0046FEE0[];
extern void OperatorDelete_100840(void *);

void *StreambufDtor_103760(void *o, s16 flag)
{
    if (o != 0) {
        *(const u8 **)o = D_0046FEE0;
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
