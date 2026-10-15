#include "types.h"

/* Named product plus an integer cast on the base -- the pair that reaches the
   `addu' operand order. */

extern void *_sceRpcGetFPacket(void);

typedef struct {
    u8 pad[0x1C];
    u8 *base;
    s32 max;
} FPacketQueue;

void *_sceRpcGetFPacket2(FPacketQueue *q, s32 rid)
{
    s32 off;

    if (rid < 0 || rid >= q->max) {
        return _sceRpcGetFPacket();
    }
    off = rid * 0x40;
    return (void *)((s32)q->base + off);
}
