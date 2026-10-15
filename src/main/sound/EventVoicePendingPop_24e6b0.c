#include "types.h"

typedef struct {
    u8 pad[0x24];
    s32 queue[8];
    s32 count;
} Queue24e6;

s32 EventVoicePendingPop_24e6b0(Queue24e6 *q)
{
    s32 ret;
    s32 i;

    if (q->count <= 0) {
        return -1;
    }
    ret = q->queue[0];
    q->count--;
    for (i = 0; i < q->count; i++) {
        q->queue[i] = q->queue[i + 1];
    }
    q->queue[q->count] = -1;
    return ret;
}
