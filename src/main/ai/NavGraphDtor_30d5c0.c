#include "types.h"

extern const u8 D_00471A50[];
extern void *NavGraphNodePoolDtor_30d660(void *, s16);
extern void *NavGraphEdgePoolDtor_30d6e0(void *, s16);
extern void *NavGraphEdgeIdxPoolDtor_30d760(void *, s16);
extern void *NavGraphStrPoolDtor_30d7d0(void *, s16);
extern void OperatorDelete_100840(void *);

void *NavGraphDtor_30d5c0(void *o, s16 flag)
{
    void *q;

    if (o != 0) {
        q = (u8 *)o + 0x90;
        if (q != 0) {
            *(const u8 **)((u8 *)o + 0x9C) = D_00471A50;
            NavGraphStrPoolDtor_30d7d0((u8 *)o + 0xD0, -1);
            NavGraphEdgeIdxPoolDtor_30d760((u8 *)o + 0xC0, -1);
            NavGraphEdgePoolDtor_30d6e0((u8 *)o + 0xB0, -1);
            NavGraphNodePoolDtor_30d660((u8 *)o + 0xA0, -1);
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
