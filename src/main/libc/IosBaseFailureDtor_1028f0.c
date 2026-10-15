#include "types.h"

extern const u8 D_0046FDB0[];
extern const u8 D_0046FD70[];
extern void *SharedArrayPtrDtor_102ab0(void *, s16);
extern void OperatorDelete_100840(void *);

void *IosBaseFailureDtor_1028f0(void *o, s16 flag)
{
    void *p;

    if (o != 0) {
        *(const u8 **)o = D_0046FDB0;
        p = (u8 *)o + 0x4;
        if (p != 0) {
            SharedArrayPtrDtor_102ab0(p, -1);
        }
        if (o != 0) {
            *(const u8 **)o = D_0046FD70;
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
