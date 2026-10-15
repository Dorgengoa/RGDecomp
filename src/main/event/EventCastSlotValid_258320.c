#include "types.h"

s32 EventCastSlotValid_258320(void *a, s32 n)
{
    if (n < 0 || n >= 0x20) {
        return 0;
    }
    return 1;
}
