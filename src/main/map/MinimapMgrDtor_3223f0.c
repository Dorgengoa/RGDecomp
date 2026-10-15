#include "types.h"

extern void DestroyArray_1005b0(void *, void *, s32, s32);
extern void MinimapSlotDtor_3225c0(void);
extern void OperatorDelete_100840(void *);

void *MinimapMgrDtor_3223f0(void *o, s16 flag)
{
    if (o != 0) {
        DestroyArray_1005b0(o, (void *)MinimapSlotDtor_3225c0, 0x1B0, 3);
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
